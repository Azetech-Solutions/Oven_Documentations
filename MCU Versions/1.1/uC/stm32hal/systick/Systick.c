
/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include "stm32g0xx.h"                
#include SYSOS_H
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
extern void TaskOverrunHanlder();
volatile uint32_t g_tick_count = 0;

void SysTick_Handler(void)
{
	TaskOverrunHanlder();
	FUN_SYS_Timer_x1();
	g_tick_count++;
}

uint32_t GetmillisX10(void)
{
    return g_tick_count;
}

void systickTimerInit(void)
{
	SysTick_Config(SystemCoreClock / 100);// This Tick Timer is Configured for 10ms Interrupt
 	NVIC_EnableIRQ (SysTick_IRQn);
	NVIC_SetPriority (SysTick_IRQn,0);
}




