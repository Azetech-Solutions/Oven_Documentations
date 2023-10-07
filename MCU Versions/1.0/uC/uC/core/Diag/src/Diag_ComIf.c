/*
 * Diag_ComIf.c
 *
 *  Created on: 15-Jun-2022
 *      Author: Hari
 */

#include "Includes.h"
#include DIAG_H
#include "ComIf.h"

/*****************************************/
/* Function Definitions                  */
/*****************************************/

UBYTE Diag_Transmit(UWORD Length, void * Data)
{
	return COMIF_EC_GENERIC_ERROR;
}

void Diag_ComIf_ErrorNotification(ULONG Debug0, ULONG Debug1)
{
	(void) Diag_ReportEvent(DiagEvent_Diag_ComIf_Error, Debug0, Debug1);
}

