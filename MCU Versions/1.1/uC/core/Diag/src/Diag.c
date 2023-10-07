/*
 * Diag.c
 *
 *  Created on: 01-May-2022
 *      Author: Hari
 */
/***************************************************/
/* Diagnostics handler Source File                 */
/***************************************************/

/***************************************************/
/* Header Inclusions                               */
/***************************************************/
#include "Includes.h"
#include DIAG_H
#include BUFFER_H
#include COMIF_H
#include IOIF_H
#include <math.h>
#include "string.h"
#include DEBUG_H
#include DAC_H
/***************************************************/
/* Global Variables Definitions                    */
/***************************************************/

DiagEventData_t *PrevDiagEventData;
DiagEventData_t DiagEventData[DiagEvent_COUNT] = {0};
UBYTE DiagFailureStatuses[DiagEventStatusByteLength] = {0};

DiagnosticsCommand_ST DiagnosticsCommand;
DiagnosticsData_ST DiagnosticsData;
DiagnosticsData_ST PrvDiagnosticsData;

BOOL DiagRxFlag = FALSE;
/***************************************************/
/* Function Definitions                            */
/***************************************************/

BOOL Diag_ReportEvent(DiagEventIdType ID, DiagEventDebugDataType debug0, DiagEventDebugDataType debug1)
{
	if(ID < DiagEvent_COUNT)
	{
		DiagEventData_t * diagEvtData = &(DiagEventData[ID]);

		/* Diag Filter Logic */
		{
			// If the Filter for the reported failure is active, then ignore the reporting
			if((DiagEventFilter[ID] & DiagActiveFilter) != 0)
			{
				// Atleast one of the configured filter is active for the failure
				DiagEventStatus[ID].IsFiltered = TRUE; // Set the Filter flag
				return 0;
			}

			DiagEventStatus[ID].IsFiltered = FALSE;
		}

		if(DiagEventStatus[ID].IsFailed == FALSE)
		{
			// Queue the event in the recent list
			Diag_RecentEvents_Buffer_EnQueue(ID);
		}
		
		/* Update Debug Data */
		diagEvtData->Error_Code  =	ID;
		diagEvtData->Debug0.Data = debug0;
		diagEvtData->Debug1.Data = debug1;

		/* Update Flags */
		DiagEventStatus[ID].IsFailed = TRUE;
		DiagEventStatus[ID].IsNewInstance = TRUE;
	}

	return 0;
}

//Diagnostic Command Rx Call back
void diagnosticCommandRxCbk(UBYTE Length, UBYTE *Data)
{
	DiagnosticsCommand.Byte = *Data;
	DiagRxFlag = TRUE;
}

void manualControls()
{
	DiagnosticsCommand_ST *cmd = &DiagnosticsCommand;

	if(DiagRxFlag == TRUE)
	{
		DiagRxFlag = FALSE;
		
		if(cmd->HOC == TRUE){if(IS_FAN_MOTOR_RUNNING()){TURN_ON_HEATER();}else{TURN_OFF_HEATER();}} else{TURN_OFF_HEATER();}

		if(cmd->DOC == TRUE){DRAIN_VALVE_OPEN();}	else{DRAIN_VALVE_CLOSE();}
		
		if(cmd->FOC == TRUE){TURN_FORWARD_MOTOR_ON(); TURN_REVERSE_MOTOR_OFF();DAC_Input(4000);}
		else{TURN_FORWARD_MOTOR_OFF();TURN_REVERSE_MOTOR_OFF();DAC_Input(0);TURN_OFF_HEATER();}
		
		if(cmd->WIOC == TRUE){TURN_ON_WATER_INLET_VALVE();}else{TURN_OFF_WATER_INLET_VALVE();}
		
		if(cmd->WPOC == TRUE){TURN_ON_WASH_PUMP();}else{TURN_OFF_WASH_PUMP();}
	}		
}


void diagnosticsData()
{
	DiagnosticsData_ST *Data = &DiagnosticsData;
	DiagnosticsData_ST *prvData = &PrvDiagnosticsData;
	//memcpy(ComIf_GetShadowBuffer_HMI_diagnosticData(),Data->Bytes,ComIf_GetLength_HMI_diagnosticData());
	UBYTE *Buff = ComIf_GetShadowBuffer_HMI_diagnosticData();
	
	if(prvData->Byte != Data->Byte)
	{
		*Buff = Data->Byte;
		
		prvData->Byte = *Buff;
		
		ComIf_TransmitFromBuffer_HMI_diagnosticData();
	}
}

/* This function must be called before the NVM Init */
void Diag_Init(void)
{

}

void Diag_MainFunction(void)
{
	manualControls();
	diagnosticsData();
	
	machineStatus_ST *MS = &machineStatus;
	
	//The Communication syncronization between app and 

	// Loop thru all event data and see if there are any new errors logged
	for(int evtId = 0; evtId < DiagEvent_COUNT; evtId++)
	{
		if(DiagEventStatus[evtId].IsNewInstance)
		{
			/* Update the Failure statuses */
			{
				UBYTE ByteIndex = (UB)ceil(evtId / 8);
				UBYTE BitIndex = evtId % 8;

				DiagFailureStatuses[ByteIndex] |= (1 << BitIndex);
			}
			
			DiagEventData_t * diagEvtData = &DiagEventData[evtId];
		
			/*The BOOT bit is used to indicate whether the Cooking mode settings have been received. If the BOOT bit is True, 
				do not log any errors because it means there is no communication between the tablet and MCU*/
			
			if(MS->BOOT == FALSE)
			{
				/*Compare the previously logged error with the current error, if they are the same, 
					do not log the error.*/
				if(memcmp(PrevDiagEventData,diagEvtData,sizeof(*diagEvtData)) != 0)
				{
					UBYTE *Buff = ComIf_GetShadowBuffer_HMI_ErrorData();//
				
					memcpy(Buff,diagEvtData->Bytes,ComIf_GetLength_HMI_ErrorData());
					
					PrevDiagEventData = diagEvtData;
					
					ComIf_TransmitFromBuffer_HMI_ErrorData();
				}
			}
			
			DiagEventStatus[evtId].IsNewInstance = FALSE;
		}
	}
}
