#ifndef USART_H
#define USART_H
/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "stm32g0xx.h"   
#include "Includes.h"

#include GPIO_H
#include COMIF_H
#include BUFFER_H
#include PLATFORM_TYPES_H

/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/

/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/

typedef UBYTE (*RxHandlerType)(UBYTE);

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/

extern BOOL IsUartCommunicationOkay;

/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
extern void uartInit();
extern void USART2_Init();

extern void DebugString(const char* data);

extern unsigned char USART_Transmit_Byte(unsigned char Data);
extern void DebugSendByte(UBYTE data);

#endif /*USART_H*/
