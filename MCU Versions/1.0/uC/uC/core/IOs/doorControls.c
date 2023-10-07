/**********************************************************/
/*          Input Output Interface	                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "IOIF.h"
#include "Includes.h"
#include WASH_H
#include DAC_H
#include DEBUG_H
#include FLOWSENSOR_H
#include DIAG_H
#include COOKING_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define STEAM_NOT_WORKING 		0u
#define STEAM_NOT_TURNING_OFF 1u

#define DOOR_STATUS_COUNTER 8
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
extern steamControlType prevSteamControl;

doorStaus_EN doorStatus = E_NotDetected;
ovenCookingState_EN PrevOvenCookingState = OCS_machineIdle;

fanMotorControlType 	prevFanMotorControl;
drainValveStatusType 	prevDrainValveStatus;
heaterControlType 		prevHeaterControl;
steamControlType		 	prevStControl;
drainValveControlType prevDrainValveControlState;
BOOL prevFanMotorRunningStatus;
BOOL OpenRequest = FALSE;

washState_EN prevWashState;

BOOL ovenPauseControl = FALSE;

volatile BOOL Is_Door_ClosedFlag;
static UBYTE DoorStatusCounter = DOOR_STATUS_COUNTER; 
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
void doorPauseControl();


void doorStatusMain()
{
	machineStatus_ST *MachineStatus = &machineStatus;
	
	if(IS_DOOR_CLOSED() == TRUE)
	{
		if(DoorStatusCounter > 0)
		{
			DoorStatusCounter--;
		}
		else
		{
			Is_Door_ClosedFlag = TRUE;
			DoorStatusCounter = DOOR_STATUS_COUNTER; 
		}
	}
	else
	{
		if(DoorStatusCounter > 0)
		{
			DoorStatusCounter--;
		}
		else
		{
			Is_Door_ClosedFlag = FALSE;
			DoorStatusCounter = DOOR_STATUS_COUNTER;
		}
	}
	
	if(Is_Door_ClosedFlag == TRUE) 
	{
		doorStatus = E_doorClosed;
		
		MachineStatus->DOI = FALSE; // Door Closed Indication
		
		if(OpenRequest == FALSE)
		{	
			if((ovenCookingState > OCS_machineIdle))
			{
				if(ovenPauseControl == TRUE)
				{
					ovenCookingState 	= PrevOvenCookingState ;
					fanMotorControl 	= prevFanMotorControl;
					heaterControl 		= prevHeaterControl	;
					steamControl 			= prevStControl	;
					
					if(prevDrainValveStatus == S_drainValveOpen)
					{
						DRAIN_VALVE_OPEN();
					}
					else
					{
						DRAIN_VALVE_CLOSE();
					}

					if(prevFanMotorRunningStatus == TRUE)
					{
						TurnOnMotor();
					}
					
					if(prevSteamControl == E_steamOn)
					{
						TURN_ON_WATER_INLET_VALVE();
					}
					else if(prevSteamControl == E_steamOff)
					{
						TURN_OFF_WATER_INLET_VALVE();
					}

					Debug_SendNumberWithDescription("ovenCookingState ",ovenCookingState);
					Debug_SendNumberWithDescription("drainValveStatus ",drainValveStatus);
					Debug_SendNumberWithDescription("fanMotorControl ",fanMotorControl);
					Debug_SendNumberWithDescription("heaterControl ",heaterControl);
					Debug_SendNumberWithDescription("steamControl ",steamControl);
					Debug_SendNumberWithDescription("MachineStatus->MachineStaus  ",MachineStatus->MachineStaus );

					ovenPauseControl = FALSE;
				}
			}
		}
	}
	else
	{
		doorStatus = E_doorOpen;
		
		MachineStatus->DOI = TRUE; // Door Open Indication
		
		if(OpenRequest == FALSE)
		{	
			if(ovenCookingState > OCS_machineIdle)
			{
				if(ovenPauseControl == FALSE)
				{
					doorPauseControl();
					ovenPauseControl = TRUE;
				}
			}
		}
	}
}

//ovenCookingState_EN ovenCookingState

void doorPauseControl()
{
	machineStatus_ST *MachineStatus = &machineStatus;
	
	if(ovenCookingState > OCS_machineIdle)
	{
		PrevOvenCookingState 				= ovenCookingState;
		prevFanMotorControl					=	fanMotorControl;
		prevDrainValveStatus				=	drainValveStatus;
		prevHeaterControl						=	heaterControl;
		prevStControl								=	steamControl;
		prevFanMotorRunningStatus 	= fanMotorRunningStatus;
		prevDrainValveControlState  =	drainValveControlState;
		
		Debug_SendNumberWithDescription("1ovenCookingState ",ovenCookingState);
		Debug_SendNumberWithDescription("1drainValveStatus ",drainValveStatus);
		Debug_SendNumberWithDescription("1fanMotorControl ",fanMotorControl);
		Debug_SendNumberWithDescription("1heaterControl ",heaterControl);
		Debug_SendNumberWithDescription("1steamControl ",steamControl);
		Debug_SendNumberWithDescription("1MachineStatus->MachineStaus  ",MachineStatus->MachineStaus );
		
		MachineStatus->MachineStaus = MS_cookingPaused;
		
		if(IsDrainValveOpen())
		{
			DRAIN_VALVE_CLOSE();
		}

		if(fanMotorControl > E_fanMotorIdle)
		{
			TURN_REVERSE_MOTOR_OFF();
			TURN_FORWARD_MOTOR_OFF();
		}

		if(IsHeaterTurnedOn())
		{
			TurnOffHeater();
		}

		if(steamControl > E_steamIdle)
		{
			TURN_OFF_WATER_INLET_VALVE();
		}
		
		Send_MachineStatus();
	}
}
