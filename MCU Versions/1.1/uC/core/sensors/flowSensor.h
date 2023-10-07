/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "stm32g0xx.h"
#include <stdio.h>
#include "Includes.h"
#include GPIO_H
#include PLATFORM_TYPES_H
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/


typedef struct
{
	ULONG volume;
	ULONG Period;
	ULONG freqencyCounter;
	ULONG freqency;
	ULONG EndTimeStamp;
	ULONG StartTimeStamp;
	ULONG MLPerMinute;
	BOOL IsFLSWorking;
	
}flowSenor_ST;

extern flowSenor_ST CH1;