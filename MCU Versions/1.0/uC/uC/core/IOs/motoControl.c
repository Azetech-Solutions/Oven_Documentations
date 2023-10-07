/**********************************************************/
/*                 motorControl						                */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "IOIF.h"
#include "Includes.h"
#include DEBUG_H
#include DAC_H
#include DIAG_H
#include DIAGIDS_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define MOTOR_REVERSE_SWITCHING_WAITIME 30 // 30 s
#define MOTOR_DIRECTION_SWITCH_TIMEOUT	300 // 5 mins
#define MOTOR_ON_OFF_TIMEOUT								15 //15s
#define MOTOR_SWITCHED_TIMEOUT					3//5s
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
fanMotorControlType fanMotorControl 	= E_fanMotorIdle;				// FanMotorControl
fanMotorControlType prevMotorControlState = E_fanMotorIdle;

BOOL fanMotorRunningStatus = FALSE;
BOOL PrvRunstatus = FALSE;
ULONG motorDirectionSwitch = MOTOR_DIRECTION_SWITCH_TIMEOUT;
UBYTE motorOnOffTimeout = MOTOR_ON_OFF_TIMEOUT;
UBYTE motorSwitchingTimeout = MOTOR_SWITCHED_TIMEOUT;
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

UBYTE updateMotorSpeed(UBYTE setThresholdLevel,UBYTE InputDACdata)
{
	/* Ex : if MaxThreshold level is 100% 
		dacMaxInputvalue = ((4095*100)/100)
		dacMaxInputvalue = 4095
	*/

	UWORD dacMaxInputvalue = (UW)(DAC_RESOLUTION*setThresholdLevel/100); 

	/* Ex : if current step level is 50% 
		dacMaxInputvalue = 4095
		InputDACdata = ((dacMaxInputvalue*10)*InputDACdata)/1000)
		InputDACdata = 2047
	*/
	UWORD DacInputDACdata =(UW) (((dacMaxInputvalue*10)*InputDACdata)/1000); 
	
	Debug_SendNumberWithDescription("DacInputDACdata: ",DacInputDACdata);
	
	DAC_Input(DacInputDACdata);
	
	//Activate the Fan motor 
	TurnOnMotor();

	return InputDACdata;
}

void motorControl()
{
	DiagnosticsData_ST *DD = &DiagnosticsData;
	machineStatus_ST *MS = &machineStatus;
	
	//This Check is used to find the motor running status
	if(IS_FAN_MOTOR_RUNNING())
	{
		PrvRunstatus = fanMotorRunningStatus;
		fanMotorRunningStatus = TRUE;
		DD->FOS = TRUE;
	}
	else
	{
		PrvRunstatus = fanMotorRunningStatus;
		fanMotorRunningStatus = FALSE;
		DD->FOS = FALSE;
	}
	
	/*The OvenPauseControl flag is used to block the execution of Motor Control procces 
	while the door is open or in the pause condition*/
	if(ovenPauseControl == FALSE)
	{
		switch(fanMotorControl)
		{
			case E_fanMotorIdle:
			{
				
			}
			break;
			case E_fanMotorRunForward:
			{
				/*To run the motor forward, first turn off the reverse motor switch and 
				then turn on the forward motor swith.if both are in High it will create problem in VFD*/
				if(motorSwitchingTimeout > 0)
				{
					if(motorSwitchingTimeout == MOTOR_SWITCHED_TIMEOUT)
					{
						TURN_REVERSE_MOTOR_OFF();
						TURN_FORWARD_MOTOR_OFF();
					}
					
					motorSwitchingTimeout--;
					Debug_SendNumberWithDescription("motorSwitchingTimeout: ",motorSwitchingTimeout);
				}
				else
				{
					TURN_FORWARD_MOTOR_ON();
					Debug_SendString("FanMotorFwd\n");
					prevMotorControlState = E_fanMotorRunForward;
					
					motorSwitchingTimeout = MOTOR_SWITCHED_TIMEOUT;
					/*reload direction switch waitimeout*/
					motorDirectionSwitch = MOTOR_DIRECTION_SWITCH_TIMEOUT;
					
					//once the IOs will be configured the state is switched to timeout state
					fanMotorControl = E_fanMotorDirectionTimout;
				}
			}
			break;
			case E_fanMotorRunReverse:
			{
				/*To run the motor Reverse, first turn off the forward motor switch and 
				then turn On the reverse motor swith.if both are in High it will create problem in VFD*/
				if(motorSwitchingTimeout > 0)
				{
					if(motorSwitchingTimeout == MOTOR_SWITCHED_TIMEOUT)
					{
						TURN_FORWARD_MOTOR_OFF();
						TURN_REVERSE_MOTOR_OFF();
					}
					
					motorSwitchingTimeout--;

					Debug_SendNumberWithDescription("motorSwitchingTimeout: ",motorSwitchingTimeout);	
				}
				else
				{
					TURN_REVERSE_MOTOR_ON();
					Debug_SendString("FanMotorReverse\n");
					prevMotorControlState = E_fanMotorRunReverse;
					
					motorSwitchingTimeout = MOTOR_SWITCHED_TIMEOUT;
					/*reload direction switch waitimeout*/
					motorDirectionSwitch = MOTOR_DIRECTION_SWITCH_TIMEOUT;
					
					//once the IOs will be configured the state is switched to timeout state
					fanMotorControl = E_fanMotorDirectionTimout;
				}
			}
			break;
			case E_fanMotorDirectionTimout:
			{
				/*Motor direction timeout is used to switch the forward and reverse direction.
				every 5 mins once it will swtich to F->R & R->F*/
				if(motorDirectionSwitch > 0)
				{
					motorDirectionSwitch--;
					//Debug_SendNumberWithDescription("motorDirectionSwitch ",motorDirectionSwitch);
				}
				else
				{		
					//This Statement Will Switch the Direction based on the previous state  
					if(prevMotorControlState == E_fanMotorRunForward)
					{
						fanMotorControl = E_fanMotorRunReverse;
					}
					else
					{
						fanMotorControl = E_fanMotorRunForward;
					}
					
					/*reload direction switch waitimeout*/
					motorDirectionSwitch = MOTOR_DIRECTION_SWITCH_TIMEOUT; 
				}
			}
			break;
			case E_fanMotor_OFF:
			{
				//To turn of the motor Forward and reverse switch will be turned off
				TURN_REVERSE_MOTOR_OFF();
				TURN_FORWARD_MOTOR_OFF();
				
				
				//The motor still runs after turning off the IOs it will log error
				if(IS_FAN_MOTOR_RUNNING())
				{	
					/*The MotorOnOffTimeout is used to delay the instant log of Motor not turning off error*/
					if(motorOnOffTimeout > 0)
					{
						motorOnOffTimeout--;
					}
					else
					{
						Diag_ReportEvent(DiagEvent_Motor_Error,MOTOR_NOT_TURNING_OFF,fanMotorControl);//Motor Not turning off
						
						fanMotorControl = E_fanMotorIdle;
						
						motorOnOffTimeout = MOTOR_ON_OFF_TIMEOUT;
					}
				}
				else{
					fanMotorControl = E_fanMotorIdle;
					motorOnOffTimeout = MOTOR_ON_OFF_TIMEOUT;
				}
			}
			break;
			default:
			{
				break;
			}
		}
		
		/*Below checked 3 states are the FanMotor running States if the fan motor is not runned in these states it
		will log an error fan motor not running*/
		if((fanMotorControl == E_fanMotorRunForward) || (fanMotorControl == E_fanMotorRunReverse) || 
		(fanMotorControl == E_fanMotorDirectionTimout))
		{	
			/*In Pause condition the Motor will not run, so before logging the error we have to check the 
			current state is in paused state or not.*/
			if((MS->MachineStaus != MS_cookingPaused) && (MS->MachineStaus != MS_washingPaused))
			{
				if(!IS_FAN_MOTOR_RUNNING())
				{
					Debug_SendNumberWithDescription("motorOnOffTimeout ",motorOnOffTimeout);
					
					if(motorOnOffTimeout > 0)
					{
						motorOnOffTimeout--;
					}
					else
					{
						TurnOnMotor();
						Diag_ReportEvent(DiagEvent_Motor_Error,MOTOR_NOT_RUNNING,fanMotorControl);//Motor Not Running
						Debug_SendNumberWithDescription("MOTOR_NOT_RUNNING ",fanMotorControl);
						motorOnOffTimeout = MOTOR_ON_OFF_TIMEOUT;
					}
				}
				else
				{
					motorOnOffTimeout = MOTOR_ON_OFF_TIMEOUT;
				}
			}				
		}
	}
}
