/**********************************************************/
/* SPI Driver				                                      */
/**********************************************************/
/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "stm32g0xx.h"                  // Device header
#include "Includes.h"
#include GPIO_H
#include PLATFORM_TYPES_H
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
extern UBYTE spiTransmitReceive(UBYTE TxData);