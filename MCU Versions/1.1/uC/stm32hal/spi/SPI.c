/**********************************************************/
/* SPI Driver				                                      */
/**********************************************************/
/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/

#include "SPI.h"
#include DEBUG_H
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
extern volatile uint32_t g_tick_count;

uint32_t timeOutCount = 0;

UBYTE activatetimeOutCount = 0;
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

extern unsigned char USART2_Transmit_Byte(unsigned char Data);

void spiInit()
{
	SPI1->CR1   	=  0x0000;

	RCC->APBENR2 |= RCC_APBENR2_SPI1EN; // Clock Enable

	SPI1->CR1		&= ~SPI_CR1_SPE ; //Peripheral enabled
	

/****************************Baud rate control******************************/
/*		FPCLK = 64 Mhz 
 *		101: fPCLK/64----> (64 Mhz / 64) = 1 Mhz
 */		
	SPI1->CR1  		|= SPI_CR1_BR_0 | SPI_CR1_BR_2; 
	
/******************************END*********************************/

	SPI1->CR1 		|= SPI_CR1_CPOL; // CPOL: Clock polarity = 0

	SPI1->CR1 		|= SPI_CR1_CPHA; //CPHA: Clock phase = 1

/****************************SPI MODE******************************/

	SPI1->CR1		&= ~SPI_CR1_RXONLY; // Full-duplex (Transmit and receive)

	SPI1->CR1 		|= SPI_CR1_MSTR; // Master configuration

/******************************END*********************************/

	SPI1->CR1			&= ~SPI_CR1_LSBFIRST; //  Data is transmitted / received with the MSB first

	SPI1->CR1			|= SPI_CR1_SSM;		//Software slave management enabled

	SPI1->CR1			|= SPI_CR1_SSI ;		//Software slave management enabled

	SPI1->CR2			&= ~SPI_CR2_DS_3;
	
	SPI1->CR2			|=	(SPI_CR2_DS_0| SPI_CR2_DS_1 | SPI_CR2_DS_2); // DS[3:0]: Data size 8 bit
	
	SPI1->CR2			|= SPI_CR2_FRXTH;
	
//	SPI1->CR2 |= SPI_CR2_RXNEIE; // Enable RXNE interrupt
	
	volatile uint32_t TempRead = SPI1->SR;

	SPI1->CR1			|= SPI_CR1_SPE ; //Peripheral enabled
	
	//NVIC_EnableIRQ(SPI1_IRQn);
}

/* Use this Function to Transmit and Receive */

UBYTE spiTransmitReceive(UBYTE TxData)
{
	UBYTE result = 0 ; 
	
	while (!(SPI1->SR &SPI_SR_TXE)); // Wait until transmit buffer is empty
	
	* ((__IO uint8_t *) &SPI1->DR) = (uint8_t) TxData ;
	
	while(SPI1->SR & SPI_SR_BSY){}; 
	
	if((SPI1->SR) & SPI_SR_RXNE)
	{
			result =  * ((__IO uint8_t *) &SPI1->DR);
	}
	
	while (((SPI1->SR) & SPI_SR_BSY)); 
		
	volatile uint32_t TempRead = SPI1->DR;						

	TempRead = SPI1->SR;
	
	return result;
}

