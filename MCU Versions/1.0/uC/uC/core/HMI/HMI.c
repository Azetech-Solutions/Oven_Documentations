/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "HMI.h"
#include UART_H
#include DAC_H
#include DIAG_H
#include DEBUG_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/

/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/


/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
BOOL IsUartBusBusy = FALSE;

extern BOOL blueToothStateBit;
/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

void HMI_ComIf_ErrorNotification(ULONG Debug0, ULONG Debug1)
{
	(void) Diag_ReportEvent(DiagEvent_HMI_ComIf_Error, Debug0, Debug1);
}


UBYTE HMI_Transmit(UWORD Length, void * Data)
{
	UBYTE retval = COMIF_EC_GENERIC_ERROR;
//		Debug_SendNumberWithDescription("blueToothStateBit: ",blueToothStateBit);
	if(blueToothStateBit == TRUE)
	{		
		if(IsUartCommunicationOkay == TRUE)
		{
			if(IsUartBusBusy == FALSE)
			{
				for(int i=0;i<Length;i++)
				{
					if(USART_Transmit_Byte(*((UB*)(Data++))))
					{
						retval = COMIF_EC_NO_ERROR;
					}
					else 
					{
						retval = COMIF_EC_TRANSMISSION_ABORTED;
						break;
					}
					
					IsUartBusBusy = TRUE;
				}
				
				if(retval == COMIF_EC_NO_ERROR)
				{
					ComIf_TxConfirmation(C_ComIfChannel_HMI); // TODO : check if its same msg is trasnsmitting again
				}
				
				IsUartBusBusy = FALSE;	
						
			}
			else
			{
				retval = COMIF_EC_CHANNEL_BUSY;
			}
		}
	}
	
	return retval;
}





