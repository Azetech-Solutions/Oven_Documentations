/*
 * Debug.c
 *
 *  Created on: 17-Apr-2021
 *      Author: Hari
 */

#include "Includes.h"
#include DEBUG_H
#include UART_H

/*****************************************/
/* Global Variables                      */
/*****************************************/

static UBYTE gs_DebugAggBuffer[DEBUG_STRING_BUFFER_SIZE];
static UBYTE gs_DebugAggCurIndex = 0;

/*****************************************/
/* Static Function Definitions           */
/*****************************************/

extern void debugMain();

void DEBUG_UART_SendString(const char * data)
{
	DebugString(data);
}

void DEBUG_UART_SendByte(UBYTE Byte)
{
	DebugSendByte(Byte);
}

static void Debug_StartAggregation(void)
{
	gs_DebugAggCurIndex = 0;
}

static void Debug_TransmitAggregatedData(void)
{
	gs_DebugAggBuffer[gs_DebugAggCurIndex] = '\0';
	DEBUG_UART_SendString((const char *)gs_DebugAggBuffer);
	gs_DebugAggCurIndex = 0;
}

static void Debug_AggregateByte(UBYTE Data)
{
	gs_DebugAggBuffer[gs_DebugAggCurIndex] = Data;
	gs_DebugAggCurIndex++;
}

#if (DEBUG_MODE == DEBUG_MODE_STRING)
static void Debug_AggregateString(const char * str)
{
	while (*str)
	{
		Debug_AggregateByte((UB)*str);
		str++;
	}
}
#endif

/*****************************************/
/* Function Definitions                  */
/*****************************************/

void Debug_SendByte(UBYTE Data)
{
#if (DEBUG_MODE == DEBUG_MODE_STRING)
	DEBUG_UART_SendByte(Data);
#endif
}


void Debug_SendString(const char * Message)
{
#if (DEBUG_MODE == DEBUG_MODE_STRING)
	DEBUG_UART_SendString(Message);
#endif
}

void Debug_SendNumber(ULONG Number)
{
#if (DEBUG_MODE == DEBUG_MODE_STRING)
	char NumberString[11] = "";
	int i = 0;

	while(Number != 0)
	{
		// Shift the Number String to the next place
		int j;
		for(j = i; j > 0; j--)
		{
			NumberString[j] = NumberString[j - 1];
		}
		NumberString[0] = ((Number % 10) + 0x30); // Convert to ASCII
		Number /= 10;
		i++;
	}

	if(i != 0)
	{
		DEBUG_UART_SendString((const char *)NumberString);
	}
	else
	{
		// If the sent value is 0, then send 0
		DEBUG_UART_SendString("0");
	}

#endif
}

void Debug_SendNumberWithDescription(const char * Text, ULONG Number)
{
#if (DEBUG_MODE == DEBUG_MODE_STRING)

	Debug_StartAggregation();
	Debug_AggregateString(Text);
	Debug_AggregateByte(':');
	Debug_TransmitAggregatedData();

	Debug_SendNumber(Number);
	
	DEBUG_UART_SendString("\n");
#endif
}

void Debug_SendTimeStamp(UBYTE Hour, UBYTE Minute, UBYTE Second)
{
#if (DEBUG_MODE == DEBUG_MODE_STRING)
	Debug_StartAggregation();
	Debug_AggregateByte((Hour/ 10) + 0x30);
	Debug_AggregateByte((Hour % 10) + 0x30);
	Debug_AggregateByte(':');
	Debug_AggregateByte((Minute / 10) + 0x30);
	Debug_AggregateByte((Minute % 10) + 0x30);
	Debug_AggregateByte(':');
	Debug_AggregateByte((Second / 10) + 0x30);
	Debug_AggregateByte((Second % 10) + 0x30);
	Debug_AggregateByte(0x0D);
	Debug_AggregateByte(0x0A);
	Debug_TransmitAggregatedData();
#endif
}

void Debug_SendMeasurementData(UBYTE ID, UBYTE DLC, UBYTE * Data, UBYTE * PrevData, UBYTE * TransmissionCount)
{
#if (DEBUG_MODE == DEBUG_MODE_MEASUREMENT)

	int i = 0;
	BOOL OkToSend = FALSE;

	/* Check if the Data has been changed from the previous transmission */
	for(i = 0; i < DLC; i++)
	{
		if(PrevData[i] != Data[i])
		{
			OkToSend = TRUE;
			break;
		}
	}

	/* Handle the Transmission Count variable */
	if(*TransmissionCount != 0)
	{
		(*TransmissionCount) -= 1;
	}

	if((OkToSend == TRUE) || (*TransmissionCount == 0))
	{
		Debug_StartAggregation();

		Debug_AggregateByte(P_DEBUG_STX);

		Debug_AggregateByte(ID);
		Debug_AggregateByte(DLC);

		for(i = 0; i < DLC; i++)
		{
			UBYTE ByteToSend = Data[i];

			if( (ByteToSend == P_DEBUG_STX)
			 || (ByteToSend == P_DEBUG_DLE)
			 || (ByteToSend == P_DEBUG_ETX)
			  )
			{
				Debug_AggregateByte(P_DEBUG_DLE);
			}

			Debug_AggregateByte(ByteToSend);
		}

		Debug_AggregateByte(P_DEBUG_ETX);

		Debug_TransmitAggregatedData();

		/* Once Sent, copy the Data to the Previous Data pointer */
		for(i = 0; i < DLC; i++)
		{
			PrevData[i] = Data[i];
		}

		/* Reset the Transmission Count every time transmitting the frame */
		*TransmissionCount = DEBUG_MEASDATA_CYCLETIME;
	}

#endif
}

void Debug_MainFunction(void)
{
	debugMain();
}
