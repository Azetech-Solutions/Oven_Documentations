/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "stm32g0xx.h"                  // Device header
#include "uart.h"
#include DEBUG_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/



/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
BOOL IsUartCommunicationOkay = FALSE;

RxHandlerType RxHandler_1;
/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
static void USART_Init(RxHandlerType RxHandler);
void USART2_Init();
void DebugSendByte(UBYTE data);

void uartInit()
{
	USART_Init(ComIf_RxIndication_HMI);
//	USART2_Init();
	IsUartCommunicationOkay = TRUE;/* TODO: Create a test message to Check the Uart Communication*/ 
}


static void USART_Init(RxHandlerType RxHandler)
{
	RxHandler_1 = RxHandler;
	/* FIFO mode is Enabled*/
	USART1->CR1 |= 		USART_CR1_FIFOEN ;
	USART1->CR3 |= (	USART_CR3_TXFTCFG_1 |	 //TXFIFO reaches 1/4 of its depth
										USART_CR3_RXFTCFG_1	);  //Receive FIFO reaches 1/4 of its depth
	
	 /*M1: Word length & M0: Word length*/
	USART1->CR1 &= (~USART_CR1_M0)|(~USART_CR1_M1);
	
		/*Oversampling 8*/
	USART1->CR1 |= USART_CR1_OVER8;
	
/**********************************************************/
/*		Baud Rate Config For Baurate 115200										
			In case of oversampling by 8: 											
			USARTDIV = 2 * 64000000 / 115200
			USARTDIV = 1111.1 (0d1111.1  = 0x457)
			BRR[3:0] = USARTDIV[3:0] >> 1 = 0x7 >> 1 = 0x3
			BRR = 0x453																					*/
/**********************************************************/

	USART1->BRR = 0x453;
	
	/* Rx & Tx Enable*/
	USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE ) ; 
	
	USART1->CR1 |= USART_CR1_RXNEIE_RXFNEIE;
	/* Stop Bits */
	USART1->CR2 &= ~USART_CR2_STOP;
	/*Enable the USART*/
	USART1->CR1 |= USART_CR1_UE;
	/*USART1 Interrupt Enable*/
	NVIC_EnableIRQ(USART1_IRQn);
}

/* UART2 for Debuging */
void USART2_Init()
{
//	/* FIFO mode is Enabled*/
//	USART2->CR1 |= 		USART_CR1_FIFOEN ;
//	USART2->CR3 |= (	USART_CR3_TXFTCFG_1);// |	 //TXFIFO reaches 1/4 of its depth
									//	USART_CR3_RXFTCFG_1	);  //Receive FIFO reaches 1/4 of its depth
	
	 /*M1: Word length & M0: Word length*/
	USART2->CR1 &= (~USART_CR1_M0)|(~USART_CR1_M1);
	
		/*Oversampling 8*/
	USART2->CR1 |= USART_CR1_OVER8;
	
/**********************************************************/
/*		Baud Rate Config For Baurate 115200										
			In case of oversampling by 8: 											
			USARTDIV = 2 * 64000000 / 115200
			USARTDIV = 1111.1 (0d1111.1  = 0x457)
			BRR[3:0] = USARTDIV[3:0] >> 1 = 0x7 >> 1 = 0x3
			BRR = 0x453																					*/
/**********************************************************/

	USART2->BRR = 0x453;
	
	/* Rx & Tx Enable*/
	USART2->CR1 |= (USART_CR1_TE );//| USART_CR1_RE ) ; 
	
	//USART2->CR1 |= USART_CR1_RXNEIE_RXFNEIE;
	/* Stop Bits */
	USART2->CR2 &= ~USART_CR2_STOP;
	/*Enable the USART*/
	USART2->CR1 |= USART_CR1_UE;
	/*USART2 Interrupt Enable*/
//	NVIC_EnableIRQ(USART2_IRQn);
}


unsigned char USART_Transmit_Byte(unsigned char Data)
{
	unsigned char retval = 0;
	
	if(USART1->ISR & USART_ISR_TXE_TXFNF)
	{
		USART1->TDR = Data;
		
		while(!(USART1->ISR & USART_ISR_TC));
		/*Transmission complete clear flag*/
		USART1->ICR |= USART_ICR_TCCF;
		retval = 1;
	}
	
	return retval;
}

unsigned char USART2_Transmit_Byte(unsigned char Data)
{
	unsigned char retval = 0;
	
	if(USART2->ISR & USART_ISR_TXE_TXFNF)
	{
		USART2->TDR = Data;
		
		while(!(USART2->ISR & USART_ISR_TC));
		/*Transmission complete clear flag*/
		USART2->ICR |= USART_ICR_TCCF;
		retval = 1;
	}
	
	return retval;
}


void USART2_String(const char* data)
{
	while(*data)
	{
		USART2_Transmit_Byte(*(data++));
	}
}

void DebugString(const char* data)
{
	while(*data)
	{
		Debug_Buffer_EnQueue(*(data++));
	}
}

void DebugSendByte(UBYTE data)
{
	Debug_Buffer_EnQueue(data);
}

void USART1_IRQHandler()
{
	__disable_irq();
	
	GPIO_TogglePin(GPIOC, GPIO_PIN_15);
	if(USART1->ISR & USART_ISR_RXNE_RXFNE)
	{
		unsigned char data = USART1->RDR;
		UART1_Buffer_EnQueue(data);
		//DebugSendByte(data);
	}
	
	__enable_irq();
}


void uartRxMain()
{
	while(!UART1_IsBufferEmpty())
	{
		UBYTE data =0 ;
		
		if(UART1_Buffer_DeQueue(&data))
		{
			RxHandler_1(data);
		}
	}
}

void debugMain()
{
	while(!Debug_IsBufferEmpty())
	{
		UBYTE data =0 ;
		
		if(Debug_Buffer_DeQueue(&data))
		{
			USART2_Transmit_Byte(data);
		}
	}
}
