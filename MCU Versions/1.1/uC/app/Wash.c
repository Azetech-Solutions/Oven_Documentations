
/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include COOKING_H
#include DIAGIDS_H
#include "Wash.h"
#include DIAG_H
#include DEBUG_H
#include FLOWSENSOR_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define WASH_WATER_INLET_RESOLUTION			60
#define DRAIN_VALVE_OPEN_TIMEOUT				60
#define WASH_WATER_100MS_FACTOR					10
#define WASH_TOGGLE_TIMEOUT							30
/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
washState_EN washState = WS_Idle;
static washState_EN prevWashState = WS_Idle;
washSettings_ST wash = {0};

static ULONG washTimoutCounter = 0;
static UBYTE washCycles = 0;
static ULONG washWaterInletTimout = 0;
static ULONG WashTurnOnCounter = WASH_TOGGLE_TIMEOUT;
static ULONG WashTurnOffCounter = WASH_TOGGLE_TIMEOUT;

static ULONG DrainValveTimeout = DRAIN_VALVE_OPEN_TIMEOUT;

BOOL WTReachedAtleastOnce = FALSE;
BOOL IsMotorTurnOnFlag = FALSE;

BOOL resumeWashBit = FALSE;

extern BOOL OpenRequest;
extern BOOL SyncFlag;
/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

void washSettingsRxCbk(UBYTE Length, UBYTE *Data)
{
	Debug_SendString("WashSettings\n");
	
	for(UBYTE i=0;i<Length;i++)
	{
		wash.Bytes[i] = *(Data++);
	}
	
	SyncFlag = TRUE;
}

void washMain()
{
	machineStatus_ST *MachineStatus = &machineStatus;
	
	washSettings_ST *Wash = &wash;
	
	if(washState > WS_Idle)
	{
		if(Wash->start == FALSE)
		{
			washState = WS_WashCompleted;
		}
	}
	
	if(ovenPauseControl == FALSE )
	{
		switch(washState)
		{
			case WS_Idle:
			{
				if(Wash->start == TRUE)
				{
					washState = WS_ConfigWashTimings;
					Debug_SendString("Wash True\n");
				}
				
				if(IsCookingIdle())
				{
					if(DrainValveTimeout > 0)
					{
						DrainValveTimeout--;
					}
					else
					{
						if(IsDrainValveOpen())
						{
							DeactivateDrainValveCtrl();
							DrainValveTimeout = DRAIN_VALVE_OPEN_TIMEOUT;
						}
					}
				}
			}
			break;
			case WS_ConfigWashTimings: 
			{
				prevWashState = washState;

				MachineStatus->MachineStaus = MS_preparingToWash;
				
				Debug_SendString("WS_ConfigWashTimings\n");
				
				if(IsDoorOpen())
				{
					prevWashState = washState;
					washState = WS_washingPaused;//pause
				}
				
				TurnOffSteam();
				TurnOffMotor();
				
				if(IsDoorClosed())
				{
					MachineStatus->DCR = FALSE;
					Send_MachineStatus();
					//Oven Cooled Down
					configuredTemprature = Wash->washTemprature;
					
					if(configuredTemprature <= 0)
					{
						Diag_ReportEvent(DiagEvent_Wash_Error,Invalid_WashTemprature,configuredTemprature);
					}
					
					washTimoutCounter = Wash->cycleOneWashPumpOnTime*WASH_WATER_INLET_RESOLUTION;
					
					if(washTimoutCounter <= 0 )
					{
						Diag_ReportEvent(DiagEvent_Wash_Error,Invalid_WashTimeOut,washTimoutCounter);
					}
					
					Debug_SendNumberWithDescription("washTimoutCounter ",washTimoutCounter);
					
					CloseDrainValve();
					
					steamLevelOnTime 	= Wash->waterInletTime*WASH_WATER_INLET_RESOLUTION*WASH_WATER_100MS_FACTOR;
					washWaterInletTimout = Wash->waterInletTime*WASH_WATER_INLET_RESOLUTION;
					steamLevelOffTime = 0;
					SteamLevelTimout 	= steamLevelOnTime;
					
					if(steamLevelOnTime <= 0)
					{
						Diag_ReportEvent(DiagEvent_Wash_Error,Invalid_SteamLevelOnTime,steamLevelOnTime);
					}
					
					SteamOn();
					
					washState = WS_waterInlet;
				}
			}
			break;
			case WS_waterInlet:
			{
				prevWashState = washState;
				
				MachineStatus->MachineStaus = MS_Washing;
				Send_MachineStatus();
				
				Debug_SendString("WS_waterInlet\n");
				
				if(IsDoorOpen())
				{
					prevWashState = washState;
					washState = WS_washingPaused;
				}
				
				if(washWaterInletTimout > 0)
				{
					washWaterInletTimout--;
					Debug_SendNumberWithDescription("washWaterInletTimout ",washWaterInletTimout);
				}
				else
				{
					washState = WS_WashPumpToggle;
					TurnOffSteam();
					updateMotorSpeed(100,75);
					TurnOnHeater();
				}
			}
			break;
			case WS_WashPumpToggle:
			{
				if(WashTurnOnCounter > 0)
				{
					if(WashTurnOnCounter == WASH_TOGGLE_TIMEOUT)
					{
						TURN_ON_WASH_PUMP();
						Debug_SendString("PUMP_ON\n");
					}
					
					WashTurnOnCounter--;
					Debug_SendNumberWithDescription("WashTurnOnCounter ",WashTurnOnCounter);
				}

				
				if(WashTurnOnCounter == 0)
				{
					if(WashTurnOffCounter > 0)
					{
						if(WashTurnOffCounter == WASH_TOGGLE_TIMEOUT)
						{
							TURN_OFF_WASH_PUMP();
							Debug_SendString("PUMP_OFF\n");
						}
						
						WashTurnOffCounter--;
						Debug_SendNumberWithDescription("WashTurnOffCounter ",WashTurnOffCounter);
					}
					else
					{
						washState = WS_Washing;
						
						WashTurnOffCounter = WASH_TOGGLE_TIMEOUT;
						WashTurnOnCounter = WASH_TOGGLE_TIMEOUT;
						
						Debug_SendString("PUMP_ON\n");
						TURN_ON_WASH_PUMP();
					}
				}
					
			}
			break;
			case WS_Washing: 
			{
				MachineStatus->MachineStaus = MS_Washing;
				
				if(IsDoorOpen())
				{
					prevWashState = washState;
					washState = WS_washingPaused;
				}
				
				Debug_SendString("WS_Washing\n");
				
				if(ovenTemprature >= configuredTemprature)
				{
					TurnOffHeater();
					TurnOffMotor();
					WTReachedAtleastOnce = TRUE;//wash temprature reached atleast once
					Debug_SendString("WTReachedAtleastOnce\n");
					IsMotorTurnOnFlag = FALSE;
				}
				else
				{
					if(ovenTemprature <= (configuredTemprature-5))
					{
						if(IsMotorTurnOnFlag == FALSE)
						{
							Debug_SendString("MO_Wash\n");
							TurnOnMotor();
							TurnOnHeater();
							IsMotorTurnOnFlag = TRUE;
						}

					}
				}
				
				if(washCycles < Wash->noOfWashCycles)
				{
					Debug_SendNumberWithDescription("washTimoutCounter ",washTimoutCounter);
					
					if(washTimoutCounter > 0)
					{
						washTimoutCounter--;
					}
					else
					{
						if(WTReachedAtleastOnce == TRUE)
						{
							TURN_OFF_WASH_PUMP();
							TurnOffHeater();
							TurnOffMotor();
							OpenDrainValve();
							washState = WS_DrainTheWashedWater;
							WTReachedAtleastOnce = FALSE;
							DrainValveTimeout = Wash->waterOutletTime*WASH_WATER_INLET_RESOLUTION;
						}
						else
						{
							TURN_OFF_WASH_PUMP();
							TurnOffHeater();
							TurnOffMotor();
							OpenDrainValve();
							washState = WS_DrainTheWashedWater;
							
							DrainValveTimeout = Wash->waterOutletTime*WASH_WATER_INLET_RESOLUTION;
							
							Diag_ReportEvent(DiagEvent_Wash_Error,WashTempratureNotAttained,ovenTemprature);
						}
					}
				}
				
				Send_MachineStatus();
			}
			break;
			case WS_DrainTheWashedWater: 
			{
				MachineStatus->MachineStaus = MS_Washing;
				
				Debug_SendString("WS_DrainTheWashedWater\n");
				
				if(IsDoorOpen())
				{
					prevWashState = washState;
					washState = WS_washingPaused;
				}
				
				if(IsDrainValveOpen())
				{
					if(DrainValveTimeout > 0)
					{
						DrainValveTimeout--;
						Debug_SendNumberWithDescription("DrainValveTimeout ",DrainValveTimeout);
					}
					else
					{
						CloseDrainValve();
						washState = WS_ReLoadTheNextWashCycleDatas;
						washCycles++;
					}
				}
			}
			break;
			case WS_ReLoadTheNextWashCycleDatas:
			{
				if(IsDoorOpen())
				{
					prevWashState = washState;
					washState = WS_washingPaused;
				}
				
				Debug_SendString("WS_ReLoadTheNextWashCycleDatas\n");
				
				if(IsDrainValveClosed())
				{
					if(washCycles < Wash->noOfWashCycles)
					{
						washTimoutCounter = Wash->cycle_2_To_N_WashPumpOnTime*WASH_WATER_INLET_RESOLUTION;
						
						if(washTimoutCounter <= 0 )
						{
							Diag_ReportEvent(DiagEvent_Wash_Error,DIAG_DEBUG_DATA_WORDS(WS_ReLoadTheNextWashCycleDatas,
							Invalid_WashTimeOut),washTimoutCounter);
						}
						
						steamLevelOnTime 	= Wash->waterInletTime*WASH_WATER_INLET_RESOLUTION*WASH_WATER_100MS_FACTOR;
						washWaterInletTimout = Wash->waterInletTime*WASH_WATER_INLET_RESOLUTION;
						steamLevelOffTime = 0;
						SteamLevelTimout 	= steamLevelOnTime;
						
						if(steamLevelOnTime <= 0)
						{
							Diag_ReportEvent(DiagEvent_Wash_Error,DIAG_DEBUG_DATA_WORDS(WS_ReLoadTheNextWashCycleDatas,
							Invalid_SteamLevelOnTime),steamLevelOnTime);
						}
						
						TurnOffHeater();
						SteamOn()	;
						
						DrainValveTimeout = Wash->waterOutletTime*WASH_WATER_INLET_RESOLUTION;
						
						if(DrainValveTimeout <= 0)
						{
							Diag_ReportEvent(DiagEvent_Wash_Error,DIAG_DEBUG_DATA_WORDS(WS_ReLoadTheNextWashCycleDatas,Invalid_DrainvalveTimeout),DrainValveTimeout);
						}
					
						CloseDrainValve();
						washState = WS_waterInlet;
					}
					else
					{
						washState = WS_WashCompleted;
					}
				}
			}
			break;
			case WS_WashCompleted:
			{
				prevWashState = washState;
				DrainValveTimeout = DRAIN_VALVE_OPEN_TIMEOUT;
				TURN_OFF_WASH_PUMP();
				MachineStatus->DOR = FALSE;
				MachineStatus->NWF = FALSE;
				OpenDrainValve();
				TurnOffHeater();
				TurnOffSteam();
				TurnOffMotor();
				washCycles = 0;
				washState = WS_Idle;
				IsMotorTurnOnFlag = FALSE;

				Wash->start = FALSE;
				
				Debug_SendString("WashCompleted\n");
				
				MachineStatus->MachineStaus = MS_machineIdle;
				Send_MachineStatus();
			}
			break;
			case WS_washingPaused:
			{
				TURN_OFF_WASH_PUMP();
				CloseDrainValve();
				TurnOffHeater();
				TurnOffSteam();
				TurnOffMotor();
				
				MachineStatus->MachineStaus = MS_washingPaused;
				
				Debug_SendString("WS_washingPaused");
				
				if(IsDoorClosed() == TRUE)
				{
					/*Resume the Previous state */
					if(prevWashState == WS_waterInlet)
					{
						SteamOn()	;								
						CloseDrainValve();
						washState = WS_waterInlet;
						Debug_SendString("Resume->WS_preparingToWash\n");
					}
					else if(prevWashState == WS_Washing)
					{
						//TURN_FORWARD_MOTOR_ON();
						TurnOnMotor();
						CloseDrainValve();
						TurnOnHeater();	
						TURN_ON_WASH_PUMP();
						washState = WS_Washing;
						Debug_SendString("Resume->WS_Washing\n");
					}
					else if(prevWashState == WS_DrainTheWashedWater)
					{
						TURN_OFF_WASH_PUMP();
						OpenDrainValve();
						washState = WS_DrainTheWashedWater;
						Debug_SendString("Resume->WS_DrainTheWashedWater\n");
					}
					else if(prevWashState == WS_ConfigWashTimings)
					{
						washState = WS_Idle;
						Debug_SendString("Resume->WS_ConfigWashTimings\n");
					}
					else if(prevWashState == WS_ReLoadTheNextWashCycleDatas)
					{
						CloseDrainValve();
						washState = WS_ReLoadTheNextWashCycleDatas;
						Debug_SendString("Resume->WS_ReLoadTheNextWashCycleDatas\n");
					}
					else
					{
						//TODO invalid Previous state log error
					}
				}
				else
				{
					Debug_SendString("Wash False\n");
				}
				
				Send_MachineStatus();
			}
			break;
			case WS_NoWaterPause:
			{
				MachineStatus->MachineStaus = MS_washingPaused;
				
				Debug_SendNumberWithDescription("MachineStatus->NWF ",MachineStatus->NWF);
				
				if(MachineStatus->NWF == TRUE)
				{
					TURN_OFF_WASH_PUMP();
					CloseDrainValve();
					TurnOffHeater();
					TurnOffMotor();
				}
				else
				{
					Debug_SendNumberWithDescription("MLP",CH1.MLPerMinute);
					
					if(CH1.MLPerMinute > 150) //|| (CH3.MLPerMiniute > 100))
					{
						if(prevWashState == WS_waterInlet)
						{
							SteamOn()	;									
							CloseDrainValve();
							washState = WS_waterInlet;
							Debug_SendString("Resume->WS_preparingToWash\n");
						}
						else if(prevWashState == WS_Washing)
						{
							//TURN_FORWARD_MOTOR_ON();
							TurnOnMotor();
							CloseDrainValve();
							TurnOnHeater();	
							TURN_ON_WASH_PUMP();
							washState = WS_Washing;
							Debug_SendString("Resume->WS_Washing\n");
						}
						else if(prevWashState == WS_DrainTheWashedWater)
						{
							TURN_OFF_WASH_PUMP();
							OpenDrainValve();
							washState = WS_DrainTheWashedWater;
							Debug_SendString("Resume->WS_DrainTheWashedWater\n");
						}
						else if(prevWashState == WS_ReLoadTheNextWashCycleDatas)
						{
							CloseDrainValve();
							washState = WS_ReLoadTheNextWashCycleDatas;
							Debug_SendString("Resume->WS_ReLoadTheNextWashCycleDatas\n");
						}
						else if(prevWashState == WS_ConfigWashTimings)
						{
							washState = WS_Idle;
							Debug_SendString("Resume->WS_preparingToWash\n");
						}
						else
						{
							washState = WS_Idle;
							Debug_SendString("Invalid WashState\n");
							//TODO invalid Previous state log error
						}
					}
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

