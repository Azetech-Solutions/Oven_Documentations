/*
 * Debug.h
 *
 *  Created on: 17-Apr-2021
 *      Author: Hari
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "Platform_Types.h"

/*************************/
/* Macro Definitions     */
/*************************/

#define DEBUG_MODE_STRING           1
#define DEBUG_MODE_MEASUREMENT      2

#define DEBUG_MODE                  DEBUG_MODE_STRING


#define DEBUG_STRING_BUFFER_SIZE    50

#define DEBUG_MEASDATA_CYCLETIME    100 // 25 seconds once --> Maximum 255 (25.5 seconds only)

#define P_DEBUG_STX                 0x7B  // Start of Text
#define P_DEBUG_DLE                 0x7C  // Data Link Escape
#define P_DEBUG_ETX                 0x7D  // End of Text


/*************************/
/* Data Type Definitions */
/*************************/


/*************************/
/* Global Variables      */
/*************************/


/*************************/
/* Function Declarations */
/*************************/

extern void Debug_SendByte(UBYTE Data);
extern void Debug_SendString(const char * Message);
extern void Debug_SendNumber(ULONG Number);
extern void Debug_SendNumberWithDescription(const char * Text, ULONG Number);
extern void Debug_SendTimeStamp(UBYTE Hour, UBYTE Minute, UBYTE Second);
extern void Debug_SendMeasurementData(UBYTE ID, UBYTE DLC, UBYTE * Data, UBYTE * PrevData, UBYTE * TransmissionCount);
extern void Debug_MainFunction(void);
extern void Debug_MeasData_MainFunction(void);

#endif /* _DEBUG_H_ */
