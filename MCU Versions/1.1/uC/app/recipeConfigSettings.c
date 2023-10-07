/**********************************************************/
/*         recipeConfigSettings                     			*/
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include "recipeConfigSettings.h"
#include COOKING_H
#include DIAGIDS_H
#include DEBUG_H
#include DIAG_H
#include IOIF_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define STEP1 0
#define STEP2 1
#define STEP3 2
#define STEP4 3
#define STEP5 4
#define STEP6 5

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
extern BOOL SyncFlag;
extern BOOL enableMultiTrayMode;

recipeStepConfig_ST recipeStepConfig;
recipeSteps_ST recipeSteps[TOTAL_NO_RECIPE_STEPS];

CS_RecipeSettings_ST 	CS_RecipeSettings[2];

bakingRecipeSettings_ST bakingRecipeSettings;

UBYTE currentStepIndex = 0;

BOOL combiRecipe_Flag 	= FALSE;
BOOL steamRecipe_Flag 	= FALSE;
BOOL bakingRecipe_Flag 	= FALSE;

recipeConfigFlags_ST RCF = {0};
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

void recipeStepConfigRxCbk(UBYTE Length, UBYTE *Data)
{
	recipeStepConfig_ST *rSC = &recipeStepConfig;
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	rSC->Byte = (UBYTE) *(Data);
	
	if((rSC->Byte != 0) && (Length == ComIf_GetLength_HMI_recipeStepConfiguration()))
	{
		RCF.recipeStepConfigFlag = TRUE;
		Debug_SendNumberWithDescription("recipeStepConfigFlag: ",RCF.recipeStepConfigFlag);
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeStepConfigError,0);
		DD->RCR = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void recipeStep1RxCbk(UBYTE Length, UBYTE *Data)
{
	recipeSteps_ST *rS1 = &recipeSteps[STEP1];
	recipeStepConfig_ST *rSconfig = &recipeStepConfig;
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	if((RCF.recipeStepConfigFlag == TRUE) && (Length == ComIf_GetLength_HMI_recipeStep1()))
	{
		for(UBYTE i =0;i < Length;i++)
		{
			rS1->Bytes[i] = *(Data++);
		}
		
		/*if the Cooking is running multi-tray mode the runtime fan speed , temprature and steam level 
		will be updated by this following logic*/
		
		if((rS1->runTimeInMinutes == 0) && (ovenCookingState > OCS_machineIdle))
		{
			configureTheCookingMode((recipeStepMode_EN)rSconfig->mode);
		}
		
		/*if the cooking mode is selected as manual. if any changes in runtime value it will Update the timing by the 
		following loggic*/
		if(IsCookingProgress())
		{	
			if(enableMultiTrayMode == FALSE)
			{
				//Convert the Total runtime in 100 ms resolution for timout calculation 
				runTimeIn100Millis = (rS1->runTimeInMinutes*600);
			}
		}
		
		RCF.recipeStep1Flag = TRUE;
		Debug_SendNumberWithDescription("recipeStep1Flag: ",RCF.recipeStep1Flag);
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeStepConfigError,1);
		DD->RCR = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void recipeStep2RxCbk(UBYTE Length, UBYTE *Data)
{
	recipeSteps_ST *rS2 = &recipeSteps[STEP2];
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	if((RCF.recipeStep1Flag == TRUE) && (Length == ComIf_GetLength_HMI_recipeStep2()))
	{		
		for(UBYTE i = 0;i < Length;i++)
		{
			rS2->Bytes[i] = *(Data++);
		}
		
		/*if and change in runtime it will Update the timing*/
		if(IsCookingProgress())
		{
			//Covert the Total runtime in 100 ms resolution for timout calculation 
			runTimeIn100Millis = (rS2->runTimeInMinutes*600);
		}

		RCF.recipeStep2Flag = TRUE;
		Debug_SendNumberWithDescription("recipeStep2Flag: ",RCF.recipeStep2Flag);
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeStep1ConfigError,1);
		DD->RCR = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void recipeStep3RxCbk(UBYTE Length, UBYTE *Data)
{
	recipeSteps_ST *rS3 = &recipeSteps[STEP3];
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	if((RCF.recipeStep2Flag == TRUE) && (Length == ComIf_GetLength_HMI_recipeStep3()))
	{
		for(UBYTE i = 0;i < Length;i++)
		{
			rS3->Bytes[i] = *(Data++);
		}
		
			/*if and change in runtime it will Update the timing*/
		if(IsCookingProgress())
		{
			//Covert the Total runtime in 100 ms resolution for timout calculation 
			runTimeIn100Millis = (rS3->runTimeInMinutes*600);
		}
		
		RCF.recipeStep3Flag = TRUE;
		Debug_SendNumberWithDescription("recipeStep3Flag: ",RCF.recipeStep3Flag);
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeStep2ConfigError,2);
		DD->RCR = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void recipeStep4RxCbk(UBYTE Length, UBYTE *Data)
{
	recipeSteps_ST *rS4 = &recipeSteps[STEP4];
	DiagnosticsData_ST *DD = &DiagnosticsData;

	if((RCF.recipeStep3Flag == TRUE) && (Length == ComIf_GetLength_HMI_recipeStep4()))
	{	
		for(UBYTE i = 0;i < Length;i++)
		{
			rS4->Bytes[i] = *(Data++);
		}
		
		/*if and change in runtime it will Update the timing*/
		if(IsCookingProgress())
		{
			//Covert the Total runtime in 100 ms resolution for timout calculation 
			runTimeIn100Millis = (rS4->runTimeInMinutes*600);
		}
	
		RCF.recipeStep4Flag = TRUE;
		Debug_SendNumberWithDescription("recipeStep4Flag: ",RCF.recipeStep4Flag);
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeStep3ConfigError,3);
		DD->RCR = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void recipeStep5RxCbk(UBYTE Length, UBYTE *Data)
{
	recipeSteps_ST *rS5 = &recipeSteps[STEP5];
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	if((RCF.recipeStep4Flag == TRUE) && (Length == ComIf_GetLength_HMI_recipeStep5()))
	{
		for(UBYTE i = 0;i < Length;i++)
		{
			rS5->Bytes[i] = *(Data++);
		}
		
		/*if and change in runtime it will Update the timing*/
		if(IsCookingProgress())
		{
			//Covert the Total runtime in 100 ms resolution for timout calculation 
			runTimeIn100Millis = (rS5->runTimeInMinutes*600);
		}
		
		RCF.recipeStep5Flag = TRUE;
		Debug_SendNumberWithDescription("recipeStep5Flag: ",RCF.recipeStep5Flag);
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeStep4ConfigError,4);
		DD->RCR = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void recipeStep6RxCbk(UBYTE Length, UBYTE *Data)
{
	recipeSteps_ST *rS6 = &recipeSteps[STEP6];
	DiagnosticsData_ST *DD = &DiagnosticsData;
	
	if((RCF.recipeStep5Flag == TRUE) && (Length == ComIf_GetLength_HMI_recipeStep6()))
	{
		for(UBYTE i = 0;i < Length;i++)
		{
			rS6->Bytes[i] = *(Data++);
		}
		
		/*if and change in runtime it will Update the timing*/
		if(IsCookingProgress())
		{
			//Covert the Total runtime in 100 ms resolution for timout calculation 
			runTimeIn100Millis = (rS6->runTimeInMinutes*600);
		}

		RCF.recipeStep6Flag = TRUE;
		Debug_SendNumberWithDescription("recipeStep6Flag: ",RCF.recipeStep6Flag);
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,RecipeStep5ConfigError,5);
		DD->RCR = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void combiRecipeRxCbk(UBYTE Length, UBYTE *Data)
{
	CS_RecipeSettings_ST *cRS = &CS_RecipeSettings[COMBI_RECIPE_INDEX];
	DiagnosticsData_ST *DD = &DiagnosticsData;
	machineStatus_ST *MS = &machineStatus;
	// this Flag is used for Clearing the boot bit
	combiRecipe_Flag  = TRUE;
	
	if(Length == ComIf_GetLength_HMI_combiRecipeSettings())
	{	
		for(UBYTE i = 0;i < Length;i++)
		{
			cRS->Bytes[i] = *(Data++);
		}
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,CombiRecipeConfigError,0);
		MS->BOOT = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void steamRecipeSettingsRxCbk(UBYTE Length, UBYTE *Data)
{
	CS_RecipeSettings_ST *sRS = &CS_RecipeSettings[STEAM_RECIPE_INDEX];
	DiagnosticsData_ST *DD = &DiagnosticsData;
	machineStatus_ST *MS = &machineStatus;
	// this Flag is used for Clearing the boot bit
	steamRecipe_Flag = TRUE;
	
	if(Length == ComIf_GetLength_HMI_steamRecipeSettings())
	{
		for(UBYTE i = 0;i < Length;i++)
		{
			sRS->Bytes[i] = *(Data++);
		}
	
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,SteamRecipeConfigError,0);
		MS->BOOT = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}

void bakingRecipeSettingsRxCbk(UBYTE Length, UBYTE *Data)
{
	bakingRecipeSettings_ST *bRS = &bakingRecipeSettings;
	DiagnosticsData_ST *DD = &DiagnosticsData;
	machineStatus_ST *MS = &machineStatus;
	// this Flag is used for Clearing the boot bit
	bakingRecipe_Flag = TRUE;
	
	if(Length == ComIf_GetLength_HMI_bakingRecipeSettings())
	{	
		for(UBYTE i = 0;i < Length;i++)
		{
			bRS->Bytes[i] = *(Data++);
		}
	}
	else
	{
		Diag_ReportEvent(DiagEvent_CookingConfig_Error,BakingRecipeConfigError,0);
		MS->BOOT = TRUE;
	}
	
	SyncFlag = TRUE;//To Check the MCU and Tablet Synchronization
}





