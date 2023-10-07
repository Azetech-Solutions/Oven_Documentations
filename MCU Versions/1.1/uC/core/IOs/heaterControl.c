/**********************************************************/
/*          Input Output Interface	                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "IOIF.h"
#include "Includes.h"
#include DAC_H
#include COOKING_H
#include DEBUG_H
#include DIAG_H

/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define HEATER_OFF_WAIT_TIMEOUT					2 // 2sec
#define HEATER_VALIDATE_COUNTER					900

/*DIAG IDs*/
#define HEATER_NOT_WORKING			0u
#define HEATER_NOT_TURNING_OFF	1u
#define FAN_MOTOR_NOT_WORKING 	2u

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/

heaterControlType heaterControl			=	E_heaterIdle;

UBYTE WaitForHeaterOff			 	=	HEATER_OFF_WAIT_TIMEOUT; //30 sec waitime for turning on the heater to ensure the motor is running
ULONG HeaterTurnOnTimeOutCounter	=	HEATER_VALIDATE_COUNTER;
ULONG HeaterTurnOffTimeOutCounter	=	HEATER_VALIDATE_COUNTER;
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

void heaterControlMain()
{
	machineStatus_ST *MachineStatus = &machineStatus;
	
	if(IsHeaterTurnedOn())
	{
		//Before turning on the heater the fan motor should run otherwise heater should not be turned on.
		if(IsFanMotorRunning())
		{
			//if the oventemprature is greater than the configuredtemprature then turn of the oven.
			if(ovenTemprature > configuredTemprature)
			{
				if(WaitForHeaterOff > 0)
				{
					WaitForHeaterOff--;
					Debug_SendString("HeaterOFF\n");
				}
				else
				{
						TURN_OFF_HEATER();
						
						//Heater on status validate counter reloading.
						HeaterTurnOnTimeOutCounter = HEATER_VALIDATE_COUNTER;
						
						//HeaterTurnOffTimeOutCounter is used to check the heater,"
					
					
						if(HeaterTurnOffTimeOutCounter > 0)
						{
							HeaterTurnOffTimeOutCounter--;
						}
						else
						{
							Diag_ReportEvent(DiagEvent_Heater_Error,HEATER_NOT_TURNING_OFF, ovenTemprature);
							
							HeaterTurnOffTimeOutCounter = HEATER_VALIDATE_COUNTER;
						}
					
					//WaitForHeaterOff = HEATER_OFF_WAIT_TIMEOUT;
						// Give indication to open the door when the Required Temprature Reached in Preheating State
						if(IsPreheating())
						{
							if(IsDoorClosed())
							{
								if(ovenTemprature > configuredTemprature)
								{
									MachineStatus->DOR = TRUE; //Give Door Open Request
									OpenRequest = TRUE;
									Send_MachineStatus();
								}
							}
						}
				}
			}
			else
			{
				/*Before turning on the heater ensure the current temprature is less than the configured temprature */ 
				if(ovenTemprature < (configuredTemprature - 3))
				{
						TURN_ON_HEATER();
					
						WaitForHeaterOff = HEATER_OFF_WAIT_TIMEOUT;
						
						HeaterTurnOffTimeOutCounter = HEATER_VALIDATE_COUNTER;
						
						if(HeaterTurnOnTimeOutCounter > 0)
						{
							HeaterTurnOnTimeOutCounter--;
						}
						else
						{
							if(ovenTemprature < configuredTemprature)
							{
								Diag_ReportEvent(DiagEvent_Heater_Error,HEATER_NOT_WORKING, ovenTemprature);
							}
							
							HeaterTurnOnTimeOutCounter = HEATER_VALIDATE_COUNTER;
						}
					}
				}
		}
		else
		{
			TURN_OFF_HEATER();
			//WaitForHeaterOff = HEATER_OFF_WAIT_TIMEOUT;
			//Diag_ReportEvent(DiagEvent_Heater_Error,FAN_MOTOR_NOT_WORKING, ovenTemprature);
			Debug_SendString("FanMotor Not Running\n");
		}
	}
	else if(IsHeaterTurnedOff())
	{
		Debug_SendString("H_Deactive\n");
		TURN_OFF_HEATER();
		HeaterTurnOnTimeOutCounter	=	HEATER_VALIDATE_COUNTER;
		HeaterTurnOffTimeOutCounter	=	HEATER_VALIDATE_COUNTER;
		heaterControl			=	E_heaterIdle;
	}
	else if(heaterControl == E_heaterIdle)
	{
		//do nothing
	}
}