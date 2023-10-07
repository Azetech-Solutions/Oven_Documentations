// for testing

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include COMIF_H
#include UART_H
#include "stdio.h"
#include DEBUG_H
#include IOIF_H
#include DIAG_H

/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
/****BLE****/
#define IS_BLE_CONNECTED()							GPIO_ReadPin(GPIOA, GPIO_PIN_15)
#define TABLET_AND_MCU_SYNC_TIMEOUT			25
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/

BOOL WDRST = FALSE;
BOOL SFTRSTF = FALSE;
BOOL PINRSTF = FALSE;
BOOL OBLRSTF = FALSE;
BOOL LPWRRSTF = FALSE;

UBYTE ResetFlag = 0;

BOOL TaskOverrunFlag = FALSE;

static UWORD bleConnectTimoutCounter = 1000;

volatile BOOL blueToothStateBit = FALSE;

BOOL 	SyncFlag = FALSE;
UBYTE TMCU_SyncCounter = TABLET_AND_MCU_SYNC_TIMEOUT;
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
extern void readVC();
extern void debugMain();
void blueToothConnectionCheck();
void Tab_Sync();
extern void USART2_String(const char* data);
extern unsigned char USART2_Transmit_Byte(unsigned char Data);
extern void calculateFlowRate();
	
void cecoInit(void)
{
	USART2_Init();
//	//Debug_SendString("Initializing");
	Debug_SendNumberWithDescription("ResetFlag ",ResetFlag);
	Debug_SendNumberWithDescription("SFTRSTF ",SFTRSTF);
	Debug_SendNumberWithDescription("PINRSTF ",PINRSTF);
	Debug_SendNumberWithDescription("OBLRSTF ",OBLRSTF);
	Debug_SendNumberWithDescription("LPWRRSTF ",LPWRRSTF);
	Debug_SendNumberWithDescription("WDRST ",WDRST);
	
	USART2_String("WDRST :");
	USART2_Transmit_Byte((UBYTE)WDRST+48);
	USART2_String("\n");
	
	USART2_String("ResetFlag :");
	USART2_Transmit_Byte((UBYTE)ResetFlag+48);
	USART2_String("\n");
	
	machineStatus_ST *MS = &machineStatus;
	MS->BOOT = TRUE;
}

void ceco_x1(void)
{
//	blueToothConnectionCheck();
//	readVC();
//	calculateFlowRate();
//	Send_MachineStatus();
}

void ceco_x10(void)
{
	
}

void ceco_x100(void)
{
	GPIO_TogglePin(GPIOC, GPIO_PIN_14);
	Tab_Sync();
}

void blueToothConnectionCheck()
{
	machineStatus_ST *MS = &machineStatus;
	
	if(IsBluetoothConnected())
	{
		blueToothStateBit = TRUE;
	}
	else
	{
		blueToothStateBit = FALSE;
		Send_MachineStatus();
	}
}



void resetHandlerInit()
{
	if(RCC->CSR & RCC_CSR_WWDGRSTF)		{ResetFlag=0;WDRST = TRUE;}
	if(RCC->CSR & RCC_CSR_IWDGRSTF)		{ResetFlag=1;}
	if(RCC->CSR & RCC_CSR_LPWRRSTF)		{ResetFlag=2;LPWRRSTF = TRUE;}
	if(RCC->CSR & RCC_CSR_OBLRSTF)		{ResetFlag=3;OBLRSTF = TRUE;}
	if(RCC->CSR & RCC_CSR_PINRSTF)		{ResetFlag=4;PINRSTF = TRUE;}
	if(RCC->CSR & RCC_CSR_SFTRSTF)		{ResetFlag=5;SFTRSTF = TRUE;}

	
	RCC->CSR = RCC_CSR_RMVF;
	uint32_t r0 = ((uint32_t*)__get_MSP())[0];
}



void TaskOverrunHanlder()
{
	if(TaskOverrunFlag == TRUE)
	{
		USART2_String("TaskOverrun\n");
	}
}

/* this Function Should Called in 1 Sec task*/
void Tab_Sync()
{
	if(TMCU_SyncCounter > 0)
	{
		TMCU_SyncCounter--;
	}
	
	if(TMCU_SyncCounter == 0)
	{
		if(SyncFlag == FALSE)
		{
				Diag_ReportEvent(DiagEvent_Synchronization_Error, 0, 0);
				Debug_SendString("DiagEvent_Synchronization_Error\n");
		}
		
		TMCU_SyncCounter = TABLET_AND_MCU_SYNC_TIMEOUT;
		
		SyncFlag = FALSE;
	}
}