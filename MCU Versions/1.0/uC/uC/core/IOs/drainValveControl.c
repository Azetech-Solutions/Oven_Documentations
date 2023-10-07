/**********************************************************/
/*          Drain Valve Control Logic                     */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "IOIF.h"
#include "Includes.h"
#include DAC_H
#include DEBUG_H
#include DIAG_H
#include COOKING_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define DRAIN_VALVE_WORKING_TIMOUT			30

#define DRAIN_VALVE_NOT_OPENING 	0u
#define DRAIN_VALVE_NOT_CLOSING		1u
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
drainValveStatusType drainValveStatus 				= S_drainValveStatusNotConfigured;
drainValveControlType drainValveControlState 	= E_DrainValveIdle;
drainValveStatusType PrevdrainValveStatus 		= S_drainValveStatusNotConfigured;

ULONG drainValveRunningTimeOut =  DRAIN_VALVE_WORKING_TIMOUT;

ULONG drainValveTimeout = 0;
ULONG drainValveOnTimeout = 0;
ULONG drainValveOffTimeout = 0;
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

UBYTE updateDrainValveSetting(ULONG onTimeout,ULONG OffTimout)
{
	drainValveOnTimeout 	= onTimeout;
	drainValveOffTimeout 	= OffTimout;
	drainValveTimeout 		= drainValveOnTimeout;
	
	if(!IsPreheating())
	{
		OpenDrainValve();
	}
	
	return drainValveTimeout;
}


void drainValveControl()
{
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	if(IS_DRAIN_VALVE_OPEN())
	{
		PrevdrainValveStatus = drainValveStatus;
		drainValveStatus = S_drainValveOpen;
		DD->DOS = TRUE;
	}
	
	if(IS_DRAIN_VALVE_CLOSED())
	{
		PrevdrainValveStatus = drainValveStatus;
		drainValveStatus = S_drainValveClosed;
		DD->DOS = FALSE;
	}
	
		/*The OvenPauseControl flag is used to block the execution of Drainvalve statemachine logic 
	while the door is open or in pause condition*/
	
	if(ovenPauseControl == FALSE)
	{
		switch(drainValveControlState)
		{
			case E_DrainValveIdle :
			{
				
			}
			break;
			case E_continouslyOpen :
			{
				/*This state is particularly used in cooking,if the previous step config temprature is in higher than the current 
				 step temprature it is used to cool down to the current temprature */
				if(IsDrainValveClosed())
				{
					DRAIN_VALVE_OPEN();
					
					if(drainValveRunningTimeOut > 0)
					{
						drainValveRunningTimeOut--;
					}
					else
					{
						Diag_ReportEvent(DiagEvent_DrainValve_Error,DRAIN_VALVE_NOT_OPENING,E_continouslyOpen);
					}
				}
				
				if(IsDrainValveOpen())
				{
					drainValveRunningTimeOut = DRAIN_VALVE_WORKING_TIMOUT;
					drainValveControlState 	= E_DrainValveIdle;
				}
			}
			break;
			case E_openDrainValve :
			{
				if(IsDrainValveClosed())
				{
					DRAIN_VALVE_OPEN();
					
					if(drainValveRunningTimeOut > 0)
					{
						drainValveRunningTimeOut--;
					}
					else
					{
						Diag_ReportEvent(DiagEvent_DrainValve_Error,DRAIN_VALVE_NOT_OPENING,E_openDrainValve);
					}
				}
				
				if(IsDrainValveOpen())
				{
					drainValveRunningTimeOut = DRAIN_VALVE_WORKING_TIMOUT;
					
					if(IsCookingProgress())
					{
						drainValveControlState = E_DrainValveOnTime;
					}
				}
			}
			break;
			case E_closeDrainValve :
			{
				if(IsDrainValveOpen())
				{
					DRAIN_VALVE_CLOSE();
					
					if(drainValveRunningTimeOut > 0)
					{
						drainValveRunningTimeOut--;
					}
					else
					{
						Diag_ReportEvent(DiagEvent_DrainValve_Error,DRAIN_VALVE_NOT_CLOSING,E_closeDrainValve);
					}
				}
				
				if(IsDrainValveClosed())
				{
					drainValveRunningTimeOut = DRAIN_VALVE_WORKING_TIMOUT;
					
					if(IsCookingProgress())
					{
						drainValveControlState = E_DrainValveOffTime;
					}
				}
			}
			break;
			case E_DrainValveOnTime :
			{
				if(IsDrainValveOpen())
				{
					if(drainValveTimeout > 0)
					{
						drainValveTimeout--;
						//Debug_SendNumberWithDescription("E_DrainValveOnTime ",drainValveTimeout);
					}
					else
					{
						drainValveTimeout = drainValveOffTimeout;//load the off time timout value
							
						drainValveControlState = E_closeDrainValve;
					}
				}
			}
			break;
			case E_DrainValveOffTime :
			{
				if(IsDrainValveClosed())
				{
					if(drainValveTimeout > 0)
					{
						drainValveTimeout--;
						//Debug_SendNumberWithDescription("E_DrainValveOffTime ",drainValveTimeout);
					}
					else
					{
						drainValveTimeout = drainValveOnTimeout;//load the off time timout value
						drainValveControlState = E_openDrainValve;
					}
				}
			}
			break;
		  case E_DeactivateDrainValveControl: 
			{
				DRAIN_VALVE_CLOSE();
				drainValveControlState = E_DrainValveIdle;
			}
			break;
			default:
			{
				break;
			}
		}
	}
}