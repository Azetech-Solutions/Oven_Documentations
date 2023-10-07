#ifndef __CECO_H__
#define __CECO_H__
/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include IOIF_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/

/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/

typedef union __WashSettings_ 
{
	struct
	{
		UBYTE coolDownTemprature:8;
		UBYTE washTemprature:8;
		UBYTE waterInletTime:8;
		UBYTE waterOutletTime:4;
		UBYTE noOfWashCycles:3;
		UBYTE start:1;
		UBYTE cycleOneWashPumpOnTime:8;
		UBYTE cycle_2_To_N_WashPumpOnTime:8;
	};
	
	UBYTE Bytes[6];
	
}washSettings_ST;

typedef enum
{
	WS_Idle = 0,
	WS_ConfigWashTimings,
	WS_preparingToWash,
	WS_waterInlet,
	WS_Washing,
	WS_WashPumpToggle,
	WS_DrainTheWashedWater,
	WS_ReLoadTheNextWashCycleDatas,
	WS_washingPaused,
	WS_NoWaterPause,
	WS_WashCompleted
	
}washState_EN;

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
extern washState_EN washState;



/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
#endif
