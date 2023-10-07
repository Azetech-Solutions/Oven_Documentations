/**********************************************************/
/*          Input Output Interface	                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "IOIF.h"
#include "Includes.h"
#include DEBUG_H
#include FLOWSENSOR_H
#include DIAG_H
#include COOKING_H
#include DIAGIDS_H
#include WASH_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define STEAMLEVEL_FACTOR	10
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
steamControlType steamControl 			= E_steamIdle;						// ValveControl

steamControlType prevSteamControl 	= E_steamIdle;

ULONG steamLevelOnTime = 0;
ULONG steamLevelOffTime = 0;

UBYTE cycleCount = 0;
UBYTE onOffStepCount = 0;
UBYTE NoWaterReportCount = 0 ;
UBYTE TurnOffIndicationCounter = 0;

ULONG SteamLevelTimout 		 	= 0;

BOOL IsWaterInletOpenFlag = FALSE;
volatile BOOL SteamTurnOff = FALSE;
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

void clearSteamLevels()
{
	steamLevelOnTime = 0;
	steamLevelOffTime = 0;
}

ULONG updateSteamLevel(UBYTE SteamLevel,CS_RecipeSettings_ST *CS_settings)
{
	if(SteamLevel == E_stemLevelLow)
	{
		steamLevelOnTime = CS_settings->steamLowLevelOntime*STEAMLEVEL_FACTOR;
		SteamLevelTimout = steamLevelOnTime;
		steamLevelOffTime = CS_settings->steamLowLevelOfftime*STEAMLEVEL_FACTOR;
	}
	else if(SteamLevel == E_stemLevelMedium)
	{
		steamLevelOnTime = CS_settings->steamMediumLevelOntime*STEAMLEVEL_FACTOR;
		SteamLevelTimout = steamLevelOnTime;
		steamLevelOffTime = CS_settings->steamMediumLevelOfftime*STEAMLEVEL_FACTOR;
	}
	else if(SteamLevel == E_stemLevelHigh)
	{
		steamLevelOnTime = CS_settings->steamHighLevelOntime*STEAMLEVEL_FACTOR;
		SteamLevelTimout = steamLevelOnTime;
		steamLevelOffTime = CS_settings->steamHighLevelOfftime*STEAMLEVEL_FACTOR;
	}
	else
	{
		steamLevelOnTime = 0;
		SteamLevelTimout = 0;
		steamLevelOffTime = 0;
	}

	//if the received timout value is zero then the steam will be turned off
	if(SteamLevelTimout == 0)
	{
		SteamTurnOff = TRUE;
	}
	else
	{
		SteamTurnOff = FALSE;
	}
		
	Debug_SendNumberWithDescription("SteamLevelTimout: ",SteamLevelTimout);
	
	return SteamLevelTimout;
}


void waterInletControl()
{
	machineStatus_ST *MachineStatus = &machineStatus;
	
	//Steam will be turn of if 
	if(SteamTurnOff == TRUE)
	{
		steamControl = E_steamDeactivate;
	}
	
	if(ovenPauseControl == FALSE)
	{
		switch(steamControl)
		{
			case E_steamIdle:
			{

			}
			break;
			case E_steamStepOnOff:
			{
				if((onOffStepCount >= 0) && (onOffStepCount < 10))
				{
					TURN_ON_WATER_INLET_VALVE();
					onOffStepCount++;
					cycleCount++;
				}
				else if((onOffStepCount >=10) && (onOffStepCount <=40))
				{
					TURN_OFF_WATER_INLET_VALVE();

					onOffStepCount++;
				}
				else
				{
					onOffStepCount = 0;
				}
				
				if(cycleCount > 50)
				{
					onOffStepCount = 0;
					cycleCount=0;
					steamControl = E_steamOn;//switch to steam off
					SteamLevelTimout = steamLevelOnTime;
				}
			}
			break;
			case E_steamOff:
			{
				TURN_OFF_WATER_INLET_VALVE();
				SteamLevelTimout = steamLevelOffTime;
				steamControl = E_steamTimeOut;
				prevSteamControl = E_steamOff;
				//Debug_SendString("E_steamOff\n");
			}
			break;
			case E_steamOn:
			{
				TURN_ON_WATER_INLET_VALVE();
				
				SteamLevelTimout = steamLevelOnTime;
				steamControl = E_steamTimeOut;
				prevSteamControl = E_steamOn;
				//Debug_SendString("E_steamOn\n");
			}
			break;
			case E_steamTimeOut:
			{
				if(SteamLevelTimout > 0 )
				{
					SteamLevelTimout--;
				//	Debug_SendNumberWithDescription("SteamLevelTimout: ",SteamLevelTimout);
				}
				else
				{
					if(prevSteamControl == E_steamOn)
					{
						steamControl = E_steamOff;
					}
					else if(prevSteamControl == E_steamOff)
					{
						steamControl = E_steamOn;//switch to steam off
					}
				}
			}
			break;
			case E_steamDeactivate:
			{
				TURN_OFF_WATER_INLET_VALVE();
				prevSteamControl 	= E_steamIdle;
				steamControl = E_steamIdle;
				NoWaterReportCount = 0;
			}
			break;
			default:
			{
				break;
			}
		}
	}
}
