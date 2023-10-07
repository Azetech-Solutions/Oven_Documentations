/*
 * Diag.h
 *
 *  Created on: 01-May-2022
 *      Author: Hari
 */

#ifndef _DIAG_H_
#define _DIAG_H_

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/

#include "Platform_Types.h"
#include "Diag_Config.h"

/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/

/* This is a direct macro to just report the error without debug data */
#define DIAG_REPORT_ERROR(x)                  Diag_ReportEvent(x, 0, 0)

/* Debug Data Configuration */
#define DIAG_DEBUG_DATA_BYTES(a, b, c, d)     ( (((UL)a) << 24) | (((UL)b) << 16) | (((UL)c) << 8) | d)
#define DIAG_DEBUG_DATA_WORDS(a, b)           ( (((UL)a) << 16) | b)

/* Length to be stored in Diag Event Item */
#define DIAG_EVENT_LENGTH				              9

/* The total number of failures configurable in the software. While changing this value, consider increasing the NVM Blocks */
#define DIAG_MAX_ALLOWED_FAILURES             100

/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/

typedef UBYTE DiagEventIdType;

typedef ULONG DiagEventDebugDataType;

typedef union __DiagDebugData_t
{
    UBYTE Bytes[4];
    ULONG Data;
}DiagDebugData_t;

typedef union __Diag_Error_Data__
{
	struct
	{
		UBYTE Error_Code;
		DiagDebugData_t Debug0;
		DiagDebugData_t Debug1;
	};
	UBYTE Bytes[DIAG_EVENT_LENGTH];
}DiagEventData_t;


typedef union __Diagnostics_Command__
{
	struct
	{ 
		UBYTE HOC 	: 1;
		UBYTE FOC 	: 1;
		UBYTE WIOC 	: 1;
		UBYTE DOC 	: 1;
		UBYTE WPOC 	: 1;
		UBYTE res 	: 3;
	};
	UBYTE Byte;
}DiagnosticsCommand_ST;

typedef union __Diagnostics_Data__
{
	struct
	{
		UBYTE RES0	:1;
		UBYTE FOS 	:1;
		UBYTE	RES1	:1;
		UBYTE DOS		:1;
		UBYTE	RES2  :3;
		UBYTE	RCR	  :1;
	};
	UBYTE Byte;
}DiagnosticsData_ST;

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/

extern DiagEventData_t DiagEventData[];
extern DiagFlags_t DiagEventStatus[];
extern UBYTE DiagFailureStatuses[];
extern DiagnosticsData_ST DiagnosticsData;

/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/


/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

extern BOOL Diag_ReportEvent(DiagEventIdType ID, DiagEventDebugDataType debug0, DiagEventDebugDataType debug1);
extern void Diag_Init(void);
extern void Diag_MainFunction(void);
extern void diagnosticsData();
#endif /* _DIAG_H_ */
