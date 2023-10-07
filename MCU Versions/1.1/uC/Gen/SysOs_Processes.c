/******************************************************************
                A Z E T E C H    S O L U T I O N S                 
-------------------------------------------------------------------
        T O O L   G E N E R A T E D   S O U R C E   C O D E        
                    D O   N O T   M O D I F Y                      
-------------------------------------------------------------------
 This file is generated with the Azetech copyrighted software tool 
 No modification should be done in this file without a written     
 consent from Azetech Solutions. Incase of any such instances,     
 Azetech Solutions will not be liable to any damages it cause.     
-------------------------------------------------------------------
 Any Distribution, Alteration, Removal, Disassemble, Decompile or  
 or Reverse Engineer the given software, without written consent   
 from Azetech Solutions by the Licensee or third parties were not  
 allowed. Such instance is considered as a breach and the Licensee 
 is the sole responsible and liable to any damages it cause.       
******************************************************************/

#include "Includes.h"
#include SYSOS_H

/**********************************
 * Global Variables Declarations
 **********************************/
BOOL Task_Overrun_Flag = FALSE;
SysOS_Ctrl_ST SysOS_Ctrl;

#if(P_SYS_OS_TASK_FACTOR_MAX > 2)
UWORD g_SysOS_Counter;
#endif


/* Extern Declaration of all the Processes */
extern void Buffer_Init(void);
extern void Debug_MainFunction(void);
extern void Diag_MainFunction(void);
extern void Diag_Config_Init(void);
extern void pllInit(void);
extern void systickTimerInit(void);
extern void gpioInit (void);
extern void uartInit(void);
extern void spiInit(void);
extern void dacInit(void);
extern void cecoInit(void);
extern void ceco_x100(void);
extern void ceco_x1(void);
extern void sensorDataMain(void);
extern void flowSensorMain(void);
extern void flowSensorInit(void);
extern void uartRxMain(void);
extern void cookingMain(void);
extern void doorStatusMain(void);
extern void ioControlMain(void);
extern void drainValveControl(void);
extern void washMain(void);
extern void resetHandlerInit(void);
extern void WDG_Sync(void);
extern void WWDG_Init(void);
extern void waterInletControl(void);
extern void calculateFlowRate(void);
extern void readVC(void);
extern void blueToothConnectionCheck(void);
extern void machineStatusMain(void);

/* Define the Process calls for the Tasks */

/* Definition for the task Init */
void PRC_SYSOS_TASK_INIT(void)
{
		resetHandlerInit();
		pllInit();
		Buffer_Init();
		gpioInit ();
		spiInit();
		Diag_Config_Init();
		cecoInit();
		dacInit();
		uartInit();
		WWDG_Init();
		flowSensorInit();
		systickTimerInit();
}

/* Definition for the task x1 */
void PRC_SYSOS_TASK_X1(void)
{
		doorStatusMain();
		uartRxMain();
		calculateFlowRate();
		readVC();
		ceco_x1();
		WDG_Sync();
}

/* Definition for the task x10 */
void PRC_SYSOS_TASK_X10(void)
{
		waterInletControl();
		blueToothConnectionCheck();
		machineStatusMain();
		Debug_MainFunction();
		Diag_MainFunction();
		cookingMain();
}

/* Definition for the task x100 */
void PRC_SYSOS_TASK_X100(void)
{
		ioControlMain();
		sensorDataMain();
		flowSensorMain();
		washMain();
		drainValveControl();
		ceco_x100();
}


void FUN_SYS_Internal_Init(void)
{
	/* Initialize All the Tasks with Factor 1 as TRUE by default */

	PRC_SYSOS_TASK_INIT();

	SysOS_Ctrl.Isx1 = TRUE;


}

void FUN_SYS_Internal_Evaluate_Tasks_x1(void)
{
	/**********************************************/
	/* Tasks with Factor 0 will not be considered */
	/* Tasks with Factor 1 will be Ignored        */
	/* Toggle the Tasks which has the factor of 2 */
	/**********************************************/

	/* Task Init Ignored as the factor was 0 */
	/* Task x1 Ignored as the factor was 1 */
	SysOS_Ctrl.Isx10 = (g_SysOS_Counter % 10) ? FALSE : TRUE;
	SysOS_Ctrl.Isx100 = (g_SysOS_Counter % 100) ? FALSE : TRUE;
#if (P_SYS_OS_TASK_FACTOR_MAX > 2)

	/* Increment the counter for next run */
	g_SysOS_Counter++;
	if(g_SysOS_Counter > P_SYS_OS_TASK_FACTOR_MAX)
	{
		/* Resetting the counter to zero will cause all tha tasks to be executed once again. */
		/* So Set the value of g_SysOS_Counter to 1	*/
		g_SysOS_Counter = 1; 
	}
#endif
}

void FUN_SYS_Internal_Execute_Tasks(void)
{
	Task_Overrun_Flag = TRUE;

	PRC_SYSOS_TASK_X1();


	if(SysOS_Ctrl.Isx10 == TRUE){ PRC_SYSOS_TASK_X10();}


	if(SysOS_Ctrl.Isx100 == TRUE){ PRC_SYSOS_TASK_X100();}

	Task_Overrun_Flag = FALSE;
}


