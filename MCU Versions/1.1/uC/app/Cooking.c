/**********************************************************/
/*          ALL PHERIPHEALS I/O INIT                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include COOKING_H
#include "DiagIDs.h"
#include IOIF_H
#include DEBUG_H
#include DIAG_H
#include FLOWSENSOR_H
#include <stdio.h>
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define STEAM_LEVEL_RESOLUTION 10

#define DRAIN_VALVE_ON_TIME 			10 // 1 min
#define DRAIN_VALVE_OFF_TIME			300 //5 mins

#define RCR_COUNTER_TIMEOUT				50
#define INVALID_DATA					0
/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
BOOL UpdateMultitrayData = FALSE;
BOOL DvOpenFlag = FALSE;
ULONG CookingRuntimeCounter = 0;
ULONG RCR_Counter = RCR_COUNTER_TIMEOUT;

ovenCookingState_EN ovenCookingState = OCS_machineIdle;
/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
->cookingMain() Function is the Main function for handling The Cooking Process
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void cookingMain()
{
	androidData_ST *AndroidData = &androidData;

	machineStatus_ST *MachineStatus = &machineStatus;

	recipeStepConfig_ST *rSconfig = &recipeStepConfig;
	
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	//Oven Light will be controlled by this light on bit
	if(AndroidData->lightOn == TRUE)
	{
		TURN_ON_LIGHT();
	}
	else
	{
		TURN_OFF_LIGHT();
	}
	
	
	/*if the oven cooking state is greater than idle state. at that time
	 if the Android startbit is false means the cooking process will be stoped*/
	if(ovenCookingState > OCS_machineIdle)
	{
		if(AndroidData->startBit == FALSE)
		{
			ovenCookingState = OCS_CookingComplete;
		}
	}
	
	/*The OvenPauseControl flag is used to block the execution of cooking procces 
	while door is open or in pause condition*/
	if(ovenPauseControl == FALSE)
	{
		switch(ovenCookingState)
		{
			case OCS_machineIdle:
			{
				if(AndroidData->startBit == TRUE)
				{
					if(MachineStatus->BOOT == FALSE)
					{
						MachineStatus->MachineStaus = MS_preparingToCook;
						Send_MachineStatus();
						//check the Recipe Settings before start the cooking
						if((RecipeSettingsRxCbkCheck() == TRUE))
						{ 
							//Cooking steps will be checked in cooking config check
							if((CookingConfigCheck((recipeStepMode_EN)rSconfig->mode) == TRUE))
							{
									/*before start cooking the door must be closed then only the cooking will be start else
									door Close request will be placed*/
									
									if(IsDoorClosed())
									{
										MachineStatus->DCR = FALSE;
										
										Send_MachineStatus();
										
										if(rSconfig->preHeat == TRUE)
										{
											ovenCookingState = OCS_preHeat;
											
											Debug_SendString("PreHeat\n");
											
											configureTheCookingMode((recipeStepMode_EN)rSconfig->mode); 

											updateDrainValveSetting(DRAIN_VALVE_ON_TIME,DRAIN_VALVE_OFF_TIME);
										}
										else
										{
											Debug_SendString("Skip_PreHeat\n");
											ovenCookingState = OCS_loadRecipeStepDatas;
										}
									}
									else
									{
										//indicate to the User The Door is open
										MachineStatus->DCR = TRUE;
										Send_MachineStatus();
									}
							}
							else
							{
								DD->RCR = TRUE;
							}
							
							RCR_Counter = RCR_COUNTER_TIMEOUT;
						}
						else
						{
							if(RCR_Counter == RCR_COUNTER_TIMEOUT)
							{
								DD->RCR = TRUE;
							}
							
							if(RCR_Counter > 0)
							{
								RCR_Counter--;
							}
							else
							{
								Debug_SendString("ConfigError\n");
								RCR_Counter = RCR_COUNTER_TIMEOUT;
								ovenCookingState = OCS_CookingComplete;
							}
						}
					}
				}
			}
			break;
			case OCS_preHeat:
			{
				//Debug_SendString("PreHeat\n");				
				MachineStatus->MachineStaus = MS_preparingToCook;
				Send_MachineStatus();
				
				/* The Door open Request flag will be set by the heater control logic once the oven reaches the configured
				temprature then the flag will set other wise it will be false*/
				
				if(MachineStatus->DOR == TRUE)
				{
					OpenDrainValve();

					if(IsDoorOpen())
					{
						ovenCookingState = OCS_waitForLoadTheFood;
						MachineStatus->DOR = FALSE;
						Debug_SendString("DorFalse\n");
						Send_MachineStatus();
					}
				}
				
				TurnOnHeater();
			}
			break;
			case OCS_waitForLoadTheFood:
			{
				TurnOffMotor();
				TurnOffHeater();
				
				if(IsDoorOpen())
				{
					MachineStatus->MachineStaus = MS_cookingPaused;
					Send_MachineStatus();
				}

				if(IsDoorClosed())
				{
					OpenRequest = FALSE;
					
					ovenCookingState = OCS_loadRecipeStepDatas;
				}
			}
			break;
			case OCS_loadRecipeStepDatas:
			{
				if(MachineStatus->MachineStaus != MS_cooking)
				{
					MachineStatus->MachineStaus = MS_preparingToCook;
					Send_MachineStatus();
				}
				
				Debug_SendString("LoadRecipedata\n");
				
				//log steps not available diag error
				if(rSconfig->numberOfSteps <= 0)
				{
					Diag_ReportEvent(DiagEvent_CookingConfig_Error, Invalid_numberOfSteps, rSconfig->numberOfSteps);
				}
				
				Debug_SendNumberWithDescription("currentStepIndex ",currentStepIndex);
				Debug_SendNumberWithDescription("numberOfSteps ",rSconfig->numberOfSteps);
				
				if(currentStepIndex < rSconfig->numberOfSteps)
				{
					//reset the counter for next cycle
					CookingRuntimeCounter = 0;
					
					configureTheCookingMode((recipeStepMode_EN)rSconfig->mode);

					updateDrainValveSetting(DRAIN_VALVE_ON_TIME,DRAIN_VALVE_OFF_TIME);
					
					TurnOnHeater();

					ovenCookingState = OCS_CookingProgress;

					/*If the last step temprature is higher then the current step temprature Open the drain valve and wait
						untill the temperature reach the configured temprature then close it
					*/
					if(currentStepIndex > 0)
					{
						if(configuredTemprature < prevConfiguredTemprature)
						{
							Debug_SendString("open the valve\n");
							/*it will open the drain valve and it does not close the valve automatically used for Cooldown the oven*/
							OpenDValve();
							DvOpenFlag = TRUE;
						}
					}
				}
				else
				{
					Debug_SendString("steps not available\n");
					ovenCookingState = OCS_CookingComplete;
				}
			}
			break;
			case OCS_CookingProgress:
			{
				MachineStatus->MachineStaus = MS_cooking;

				if(DvOpenFlag == TRUE)
				{
					if(ovenTemprature <= configuredTemprature)
					{
						/*This function will open the drain valve and works in cyclicaly on and off*/
						OpenDrainValve();
						Debug_SendString("ValveOpened\n");
						DvOpenFlag = FALSE;
					}
				}

				if(enableMultiTrayMode == FALSE)
				{
					if(CookingRuntimeCounter <= runTimeIn100Millis)
					{
						CookingRuntimeCounter++;
						
						if((CookingRuntimeCounter%100)==0)
							Debug_SendNumberWithDescription("CookingRuntimeCounter: ",CookingRuntimeCounter);
					}
					else
					{
						recipeSteps[currentStepIndex].disable = TRUE;
						currentStepIndex++;

						if(currentStepIndex < rSconfig->numberOfSteps)
						{
							ovenCookingState = OCS_loadRecipeStepDatas;
						}
						else
						{
							ovenCookingState = OCS_CookingComplete;
						}
					}
				}
			}
			break;
			case OCS_CookingComplete:
			{
				Debug_SendString("OCS_CookingComplete\n");
				/*Once cooking Complete reset the Global variables and also turn off all actuator*/
				MachineStatus->DOR = FALSE; 
				OpenRequest = FALSE;
				MachineStatus->NWF = FALSE;
				currentStepIndex = 0;
				RCF.Byte = 0 ; //Recipe Configuration Flags Cleared after completion of Cooking
				TurnOffMotor();
				OpenDrainValve();
				TurnOffSteam();
				TurnOffHeater();
				CookingRuntimeCounter = 0;
				prevConfiguredTemprature = 0;
				enableMultiTrayMode  = FALSE;
				DvOpenFlag = FALSE;
				
				if(AndroidData->startBit == FALSE)
				{
					ovenCookingState = OCS_machineIdle;
				}

				MachineStatus->MachineStaus = MS_machineIdle;
				Send_MachineStatus();
			}
			break;
			case OCS_NoWaterCookingPaused:
			{
				MachineStatus->MachineStaus = MS_cookingPaused;
			
				TurnOffMotor();
				CloseDrainValve();
				TurnOffHeater();
				Debug_SendString("cookingPaused\n");

				if(MachineStatus->NWF == FALSE)
				{
					ovenCookingState = OCS_CookingProgress;

					TurnOnMotor();
					OpenDrainValve();
					TurnOnHeater();
					
					if((rSconfig->mode == E_steam) || (rSconfig->mode == E_combination))
					{
						SteamOn();
					}
					
					Send_MachineStatus();
					Debug_SendString("Resumed\n");
					//reload the needed datas and restart the cooking
				}
			}
			break;
			default:
			{
				break;
			}
		}
	}
}
