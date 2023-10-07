/**********************************************************/
/*          Input Output Interface	                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "IOIF.h"
#include "Includes.h"
#include WASH_H
#include DEBUG_H
#include DIAG_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
machineStatus_ST machineStatus = {0};
static machineStatus_ST prevMachineStatus = {0};
UBYTE MsTimeOutCount = 0;

extern BOOL combiRecipe_Flag ;
extern BOOL steamRecipe_Flag ;
extern BOOL bakingRecipe_Flag;

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
extern void motorControl();
extern void heaterControlMain();
extern void waterInletControl();

void machineStatusMain()
{
	UBYTE *Buffer = ComIf_GetShadowBuffer_HMI_machineStatus();

	machineStatus_ST *data = &machineStatus;
	machineStatus_ST *prev = &prevMachineStatus;
	
	if(prev->Byte !=  data->Byte)
	{
		UBYTE Lenth = ComIf_GetLength_HMI_machineStatus();

		*Buffer = data->Byte;
		
		prev->Byte = *Buffer;
		
		ComIf_TransmitFromBuffer_HMI_machineStatus();
	}
	else
	{
		if(MsTimeOutCount >= 5)
		{
			UBYTE Lenth = ComIf_GetLength_HMI_machineStatus();

			*Buffer = data->Byte;
			
			prev->Byte = *Buffer;
			
			ComIf_TransmitFromBuffer_HMI_machineStatus();
			
			MsTimeOutCount = 0;
		}
	}
}



void HMI_TxConfCbk()
{
	machineStatus_ST *MS = &machineStatus;
	
	if(MS->BOOT == TRUE)
	{
		Debug_SendString("BootBitTrue\n");
	}
	
	if(((combiRecipe_Flag == TRUE)&&(steamRecipe_Flag == TRUE)&&(bakingRecipe_Flag == TRUE)))
	{
		if(MS->BOOT  == TRUE)
		{
			MS->BOOT = FALSE;
			Debug_SendString("BootBitFalse\n");
		}
		
		combiRecipe_Flag = FALSE;
		steamRecipe_Flag = FALSE;
		bakingRecipe_Flag = FALSE;
	}
}


void ioControlMain()
{
	MsTimeOutCount++;
	motorControl();
	heaterControlMain();
}
