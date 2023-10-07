/**********************************************************/
/*          ALL PHERIPHEALS I/O INIT                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/

#include "Includes.h"
#include COOKING_H
#include IOIF_H
#include DEBUG_H
#include DIAG_H
#include <stdio.h>
#include "DiagIDs.h"
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define STEAM_LEVEL_RESOLUTION 10

#define DRAIN_VALVE_ON_TIME 			30 // 1 min
#define DRAIN_VALVE_OFF_TIME			30 //3 mins

#define INVALID_DATA					0

#define CookingDR(x) 	Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeConfigFlagCheck, x);

#define PREHEAT_MAX_FAN_SPEED 100
/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
androidData_ST androidData;

recipeStepMode_EN recipeStepMode;

machineStaus_EN machine_Status = MS_machineIdle;

UWORD maximumTemprature = 0;

ULONG runTimeIn100Millis = 0;

volatile UWORD configuredTemprature;

volatile UWORD prevConfiguredTemprature;

BOOL enableMultiTrayMode = FALSE;

extern BOOL SyncFlag;
extern volatile BOOL SteamTurnOff;
/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

void androidDataRxCbk(UBYTE Length, UBYTE *Data)
{
	for(UB i=0;i<Length;i++)
	{
		androidData.Bytes[i] = *(Data++);
	}
	
	SyncFlag = TRUE;
}


void configureTheCookingMode(recipeStepMode_EN Mode)
{
	recipeStepConfig_ST *rSconfig = &recipeStepConfig;
	
	switch(Mode)
	{
		case E_undefined:
		{
			Diag_ReportEvent(DiagEvent_CookingConfig_Error, Invalid_CookingMode, E_undefined);
		}
		break;
		case E_hotAir:
		{
			if(!(recipeSteps[currentStepIndex].disable))
			{
				//To identify the wrong step index
				if(currentStepIndex != (recipeSteps[currentStepIndex].stepNumber - 1))
				{
					Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(E_hotAir,Invalid_StepIndex),
					DIAG_DEBUG_DATA_WORDS(currentStepIndex ,recipeSteps[currentStepIndex].stepNumber));
				}
				
				if(IsPreheating() && (rSconfig->preHeat == TRUE))
				{
					Debug_SendNumberWithDescription("bakingpreHeatFanSpeed ",bakingRecipeSettings.preHeatFanSpeed);
					// Update Fan Speed to VFD and Turn On the Motor
					updateMotorSpeed(PREHEAT_MAX_FAN_SPEED,bakingRecipeSettings.preHeatFanSpeed);
				}
				else
				{
					// Update Fan Speed to VFD and Turn On the Motor
					updateMotorSpeed(bakingRecipeSettings.maxFanSpeed,recipeSteps[currentStepIndex].fanSpeed);
				}
				
				/*Copy the HMI Configured temprature*/
				prevConfiguredTemprature = configuredTemprature;
				
				configuredTemprature = ((recipeSteps[currentStepIndex].tempratureMSB << 2) | (recipeSteps[currentStepIndex].tempratureLSB));
				
				ULONG maximumTemprature = ((bakingRecipeSettings.maxTempratureMSB << 2) | (CS_RecipeSettings[COMBI_RECIPE_INDEX].maxTempratureLSB));
				
				if(configuredTemprature > maximumTemprature)
				{
					configuredTemprature = maximumTemprature;
					Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(E_hotAir,Invalid_MaxTemprature), maximumTemprature);
					//report set temprature is exceed the limit
				}
				
				//Covert the Total runtime in 100 ms resolution for timout calculation
				runTimeIn100Millis =  (recipeSteps[currentStepIndex].runTimeInMinutes*600);
				
				if(runTimeIn100Millis == 0)
				{
					enableMultiTrayMode = TRUE;
				}
			}
		}
		break;
		case E_steam:
		{
			if(!(recipeSteps[currentStepIndex].disable))
			{
				//To identify the wrong step index
				if(currentStepIndex != (recipeSteps[currentStepIndex].stepNumber - 1))
				{
					Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(E_steam,Invalid_StepIndex),
					DIAG_DEBUG_DATA_WORDS(currentStepIndex ,recipeSteps[currentStepIndex].stepNumber));
				}
					
				/*Config the Steam levels*/
				updateSteamLevel(recipeSteps[currentStepIndex].steamLevel,&CS_RecipeSettings[STEAM_RECIPE_INDEX]);
			
				if((!IsPreheating()) && (!IsCookingIdle()))
				{
					if(currentStepIndex == 0)
					{
						TurnOnSteam(); // it will turn on the water inlet level
					}
					else
					{
						SteamOn();
					}
				}
				
				if(IsPreheating() && (rSconfig->preHeat == TRUE))
				{
					Debug_SendNumberWithDescription("SpreHeatFanSpeed ",CS_RecipeSettings[STEAM_RECIPE_INDEX].preHeatFanSpeed);
					// Update Fan Speed to VFD and Turn On the Motor
					updateMotorSpeed(PREHEAT_MAX_FAN_SPEED,CS_RecipeSettings[STEAM_RECIPE_INDEX].preHeatFanSpeed);
				}
				else
				{
					/* Update Fan Speed to VFD and Turn On the Motor */
					updateMotorSpeed(CS_RecipeSettings[STEAM_RECIPE_INDEX].maxFanSpeed,recipeSteps[currentStepIndex].fanSpeed);
				}
				
				/*Copy the HMI Configured temprature*/
				prevConfiguredTemprature = configuredTemprature;
				
				configuredTemprature = ((recipeSteps[currentStepIndex].tempratureMSB << 2) | (recipeSteps[currentStepIndex].tempratureLSB));
				
				ULONG maximumTemprature = ((CS_RecipeSettings[STEAM_RECIPE_INDEX].maxTempratureMSB << 2) | (CS_RecipeSettings[STEAM_RECIPE_INDEX].maxTempratureLSB));

				if(configuredTemprature > maximumTemprature)
				{
					configuredTemprature = maximumTemprature;
					//report set temprature is exceed the limit
					Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(E_steam,Invalid_MaxTemprature), maximumTemprature);
				}
				
				//Covert the Total runtime in 100 ms resolution for timout calculation
				runTimeIn100Millis =  (recipeSteps[currentStepIndex].runTimeInMinutes*600); 
				
				if(runTimeIn100Millis == 0)
				{
					enableMultiTrayMode = TRUE;
				}
			}
		}
		break;
		case E_combination:
		{
			if(!(recipeSteps[currentStepIndex].disable))
			{
				//To identify the wrong step index
				if(currentStepIndex != (recipeSteps[currentStepIndex].stepNumber - 1))
				{
					Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(E_combination,Invalid_StepIndex),
					DIAG_DEBUG_DATA_WORDS(currentStepIndex ,recipeSteps[currentStepIndex].stepNumber));
				}
				
				/*Config the Steam levels*/
				updateSteamLevel(recipeSteps[currentStepIndex].steamLevel,&CS_RecipeSettings[COMBI_RECIPE_INDEX]);
				
				if((!IsPreheating()) && (!IsCookingIdle()))
				{
					if(currentStepIndex == 0)
					{
						TurnOnSteam(); // it will turn on the water inlet level
					}
					else
					{
						SteamOn();
					}
				}
				
				if(IsPreheating() && (rSconfig->preHeat == TRUE))
				{
					// Update Fan Speed to VFD and Turn On the Motor
					updateMotorSpeed(PREHEAT_MAX_FAN_SPEED,CS_RecipeSettings[COMBI_RECIPE_INDEX].preHeatFanSpeed);
				}
				else
				{
					/* Update Fan Speed to VFD and Turn On the Motor */
					updateMotorSpeed(CS_RecipeSettings[COMBI_RECIPE_INDEX].maxFanSpeed,recipeSteps[currentStepIndex].fanSpeed);
				}
				
				/*Copy the HMI Configured temprature*/
				prevConfiguredTemprature = configuredTemprature;
			
				configuredTemprature = (UWORD)((recipeSteps[currentStepIndex].tempratureMSB << 2) | (recipeSteps[currentStepIndex].tempratureLSB));
				
				Debug_SendNumberWithDescription("configuredTemprature: ",configuredTemprature);
				
				UWORD maximumTemprature = ((CS_RecipeSettings[COMBI_RECIPE_INDEX].maxTempratureMSB << 2) | (CS_RecipeSettings[COMBI_RECIPE_INDEX].maxTempratureLSB));
				
				if(configuredTemprature > maximumTemprature)
				{
					configuredTemprature = maximumTemprature;
					Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(E_combination,Invalid_MaxTemprature), maximumTemprature);
					//report set temprature is exceed the limit
				}

				//Covert the Total runtime in 100 ms resolution for timout calculation
				runTimeIn100Millis =  (recipeSteps[currentStepIndex].runTimeInMinutes*600); 
				
				if(runTimeIn100Millis == 0)
				{
					enableMultiTrayMode = TRUE;
				}
			}
		}
		break;
		default:
		{
			Diag_ReportEvent(DiagEvent_CookingConfig_Error, Invalid_CookingMode, Mode);
			break;
		}
	}
}

BOOL RecipeSettingsRxCbkCheck()
{
	BOOL retval = FALSE;
	
	recipeStepConfig_ST *rSconfig = &recipeStepConfig;
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	Debug_SendNumberWithDescription("numberOfSteps: ",rSconfig->numberOfSteps);
	Debug_SendNumberWithDescription("RCF.Byte: ",RCF.Byte);
	
	if(rSconfig->numberOfSteps == 1)
	{ 
		if (RCF.Byte == 3)		{retval = TRUE;DD->RCR = FALSE;}
		else{RCF.Byte=0;retval = FALSE;CookingDR(DIAG_DEBUG_DATA_WORDS(RCF.Byte,rSconfig->numberOfSteps));}
	}
	else if(rSconfig->numberOfSteps == 2)
	{
		if(RCF.Byte == 7)			{retval = TRUE;DD->RCR = FALSE;}
		else{RCF.Byte=0;retval = FALSE;CookingDR(DIAG_DEBUG_DATA_WORDS(RCF.Byte,rSconfig->numberOfSteps));}
	}
	else if(rSconfig->numberOfSteps == 3)
	{
		if(RCF.Byte == 15)		{retval = TRUE;DD->RCR = FALSE;}
		else{RCF.Byte=0;retval = FALSE;CookingDR(DIAG_DEBUG_DATA_WORDS(RCF.Byte,rSconfig->numberOfSteps));}
	}
	else if(rSconfig->numberOfSteps == 4) 
	{ 
		if(RCF.Byte == 0x1F)	{retval = TRUE;DD->RCR = FALSE;}
		else{RCF.Byte=0;retval = FALSE;CookingDR(DIAG_DEBUG_DATA_WORDS(RCF.Byte,rSconfig->numberOfSteps));}
	}
	else if(rSconfig->numberOfSteps == 5) 
	{
		if(RCF.Byte == 0x3F)	{retval = TRUE;DD->RCR = FALSE;}
		else{RCF.Byte=0;retval = FALSE;CookingDR(DIAG_DEBUG_DATA_WORDS(RCF.Byte,rSconfig->numberOfSteps));}
	}
	else if(rSconfig->numberOfSteps == 6)
	{	
		if(RCF.Byte == 0x7F)	{retval = TRUE;DD->RCR = FALSE;}
		else{RCF.Byte=0;retval = FALSE;CookingDR(DIAG_DEBUG_DATA_WORDS(RCF.Byte,rSconfig->numberOfSteps));}
	}
	else
	{
		//TODO: invalid No.steps
		Debug_SendString("InvalidStep\n");
	}
	
	return retval;
}


BOOL CookingConfigCheck(recipeStepMode_EN Mode)
{
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	BOOL retval = TRUE;
	
	recipeStepConfig_ST *rSconfig = &recipeStepConfig;
	
	for(UBYTE CurrentIndex = 0;CurrentIndex < rSconfig->numberOfSteps;CurrentIndex++)
	{
		switch(Mode)
		{
			case E_undefined:
			{
				Diag_ReportEvent(DiagEvent_CookingConfig_Error, Invalid_CookingMode, E_undefined);
				DD->RCR = TRUE;
				retval = FALSE;
				return retval;
			}
			break;
			case E_hotAir:
			{
				if(!(recipeSteps[CurrentIndex].disable))
				{
					//To identify the wrong step index
					if(CurrentIndex != (recipeSteps[CurrentIndex].stepNumber - 1))
					{
						Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(1,Invalid_StepIndex),
						DIAG_DEBUG_DATA_WORDS(CurrentIndex ,recipeSteps[CurrentIndex].stepNumber));
						
						DD->RCR = TRUE;
						retval = FALSE;
						return retval;
					}
				}
			}
			break;
			case E_steam:
			{
				if(!(recipeSteps[CurrentIndex].disable))
				{
					//To identify the wrong step index
					if(CurrentIndex != (recipeSteps[CurrentIndex].stepNumber - 1))
					{
						Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(2,Invalid_StepIndex),
						DIAG_DEBUG_DATA_WORDS(CurrentIndex ,recipeSteps[CurrentIndex].stepNumber));
						
						DD->RCR = TRUE;
						retval = FALSE;
						return retval;
					}
				}
			}
			break;
			case E_combination:
			{
				if(!(recipeSteps[CurrentIndex].disable))
				{
					//To identify the wrong step index
					if(CurrentIndex != (recipeSteps[CurrentIndex].stepNumber - 1))
					{
						Diag_ReportEvent(DiagEvent_CookingConfig_Error,DIAG_DEBUG_DATA_WORDS(3,Invalid_StepIndex),
						DIAG_DEBUG_DATA_WORDS(CurrentIndex ,recipeSteps[CurrentIndex].stepNumber));
			
						DD->RCR = TRUE;
						retval = FALSE;
						return retval;
					}
				}
			}
			break;
			default:
			{
				Diag_ReportEvent(DiagEvent_CookingConfig_Error, Invalid_CookingMode, Mode);
				DD->RCR = TRUE;
				retval = FALSE;
				return retval;
			}
		}
	}
	
	Debug_SendNumberWithDescription("retval ",retval);
	return retval;
}
