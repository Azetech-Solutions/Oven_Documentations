#ifndef _OVENMAINFUNC_
#define _OVENMAINFUNC_
/**********************************************************/
/*          ALL PHERIPHEALS I/O INIT                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/

#include "Includes.h"
#include COMIF_H
#include RECIPECONFIGSETTINGS_H

/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define IsResumState()					(ovenCookingState == OCS_resumCooking)
#define IsPreheating()					(ovenCookingState == OCS_preHeat)
#define IsCookingIdle()					(ovenCookingState == OCS_machineIdle)
#define IsCookingProgress()			(ovenCookingState == OCS_CookingProgress)
#define PauseTheCooking()				(ovenCookingState = OCS_NoWaterCookingPaused)
/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/


typedef union __CommandData_ST
{
	struct
	{
		/* Byte-0 */
		UBYTE batteryLevel	: 8;
		/* Byte-1 */
		UBYTE online				: 1;
		UBYTE mqtt					: 1;
		UBYTE lightOn				: 1;
		UBYTE res1					:	1;
		UBYTE sdr						: 1;
		UBYTE bcs						: 1;
		UBYTE startBit			:	1;
		UBYTE res					  : 1;
	};
	
	UBYTE Bytes[2];
	
}androidData_ST;

typedef enum
{
	OCS_machineIdle = 0,
	OCS_preHeat,
	OCS_waitForLoadTheFood,
	OCS_waitForDoorClose,
	OCS_loadRecipeStepDatas,
	OCS_CookingProgress,
	OCS_CookingComplete,
	OCS_NoWaterCookingPaused,
	
}ovenCookingState_EN;


typedef enum
{
	E_undefined = 0,
	E_hotAir,
	E_steam,
	E_combination
	
}recipeStepMode_EN;

typedef enum
{
	E_steamLevelNotConfigured = 0,
	E_stemLevelLow,
	E_stemLevelMedium ,
	E_stemLevelHigh
	
}steamLevel_EN;


/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
extern ovenCookingState_EN ovenCookingState;
extern androidData_ST androidData;

extern volatile UWORD ovenTemprature;
extern volatile UWORD configuredTemprature;
extern volatile UWORD prevConfiguredTemprature;

extern UWORD maximumTemprature;
extern ULONG runTimeIn100Millis;
extern ULONG steamLevelOnTime;
extern ULONG steamLevelOffTime;
extern BOOL UpdateMultitrayData; 
extern BOOL enableMultiTrayMode;

extern void configureTheCookingMode(recipeStepMode_EN Mode);
extern BOOL CookingConfigCheck(recipeStepMode_EN Mode);
extern ULONG updateSteamLevel(UBYTE SteamLevel,CS_RecipeSettings_ST *CS_settings);
extern BOOL RecipeSettingsRxCbkCheck();


/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/


#endif