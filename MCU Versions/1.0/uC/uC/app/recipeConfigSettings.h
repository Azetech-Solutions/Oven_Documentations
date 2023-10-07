#ifndef _RecipeConfigSettings_H
#define _RecipeConfigSettings_H
/**********************************************************/
/*         recipeConfigSettings                     			*/
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include COMIF_H

/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define TOTAL_NO_RECIPE_STEPS		6
#define COMBI_RECIPE_INDEX      0
#define STEAM_RECIPE_INDEX      1
/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/


typedef union _RecipeStepConfig
{
	struct
	{
		/***Byte 0***/
		UBYTE numberOfSteps : 3;
		UBYTE mode : 2;
		UBYTE preHeat:1;
		UBYTE res : 2;
	};
	
	UBYTE Byte;
	
}recipeStepConfig_ST;

typedef union _RecipeSteps
{
	struct
	{
		/***Byte 0***/
		UBYTE fanSpeed : 8	;
		/***Byte 1***/
		UBYTE tempratureMSB : 8;
		/***Byte 2***/
		UBYTE stepNumber : 3;
		UBYTE disable : 1;
		UBYTE steamLevel : 2;
		UBYTE tempratureLSB : 2;
		/***Byte 3***/
		UBYTE runTimeInMinutes : 8;
	};
	
	UBYTE Bytes[4];

}recipeSteps_ST;

/* Combi and Steam recipe Settings */

typedef union _CS_RecipeSettings
{
	struct
	{
		/***Byte 0***/
		UBYTE maxFanSpeed : 8	;
		/***Byte 1***/
		UBYTE maxTempratureMSB : 8;
		/***Byte 2***/
		UBYTE steamLowLevelOntime : 6;
		UBYTE maxTempratureLSB : 2;
		/***Byte 3***/
		UBYTE steamLowLevelOfftime : 8;
		/***Byte 4***/
		UBYTE steamMediumLevelOntime : 8;
		/***Byte 5***/
	  UBYTE steamMediumLevelOfftime : 8;
		/***Byte 6***/
		UBYTE steamHighLevelOntime : 8;
		/***Byte 7***/
	  UBYTE steamHighLevelOfftime : 8;
		/***Byte 8***/
		UBYTE preHeatFanSpeed : 8;
	};
	
	UBYTE Bytes[9];

}CS_RecipeSettings_ST;


typedef union
{
	struct
	{
		/***Byte 0***/
		UBYTE maxFanSpeed : 8;
		/***Byte 1***/
		UBYTE maxTempratureMSB 	: 8;
		/***Byte 2***/
		UBYTE maxTempratureLSB 	: 2;
		UBYTE reserved 		: 6;
		/***Byte 3***/
		UBYTE preHeatFanSpeed : 8;
	};
	
	UBYTE Bytes[4];
}bakingRecipeSettings_ST;
	
typedef union _RecipeConfigFlags
{
	struct
	{
		/***Byte 0***/
		UBYTE recipeStepConfigFlag:1;
		UBYTE recipeStep1Flag : 1;
		UBYTE recipeStep2Flag : 1;
		UBYTE recipeStep3Flag : 1;
		UBYTE recipeStep4Flag : 1;
		UBYTE recipeStep5Flag : 1;
		UBYTE recipeStep6Flag : 1;
		
		UBYTE RES:1;
	};
	
	UBYTE Byte;
	
}recipeConfigFlags_ST;
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/

/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

extern UBYTE currentStepIndex;
extern recipeSteps_ST recipeSteps[TOTAL_NO_RECIPE_STEPS];
extern recipeStepConfig_ST recipeStepConfig;
extern CS_RecipeSettings_ST CS_RecipeSettings[2];
extern bakingRecipeSettings_ST bakingRecipeSettings;
extern recipeConfigFlags_ST RCF;
#endif