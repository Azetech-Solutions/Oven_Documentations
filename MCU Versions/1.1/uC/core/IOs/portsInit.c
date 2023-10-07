/**********************************************************/
/*          ALL PHERIPHEALS I/O INIT                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include PORTSINIT_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/

/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/

/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

void gpioClockEnable()
{
	/* GPIO Ports Clock Enable */
	PORTA_CLOCK_ENABLE();
	PORTB_CLOCK_ENABLE();
	PORTC_CLOCK_ENABLE();
	PORTD_CLOCK_ENABLE();
}

void outputControls()
{
	GPIO_InitTypeDef PD0_PD2_PD5,PC0 = {0};
	
	/*Configure GPIO pin Output Level */
  
	GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5, GPIO_PIN_RESET);
 
	/*Configure GPIO pins : 
	<-> PD0 ---> Heater 
	<-> PD1 ---> Water Inlet
	<-> PD2 ---> WashPump
	<-> PD5 ---> Light 
	*/

  PD0_PD2_PD5.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5;
  PD0_PD2_PD5.Mode = GPIO_MODE_OUTPUT_PP;
  PD0_PD2_PD5.Pull = GPIO_NOPULL;
  PD0_PD2_PD5.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Config(GPIOD, &PD0_PD2_PD5);
	
	/*Configure GPIO pin : 
	<-> PC0 ---> Tablet Charging Control 
	*/
	
	/*Configure GPIO pin Output Level */
  GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	
  PC0.Pin = GPIO_PIN_0|GPIO_PIN_8;
  PC0.Mode = GPIO_MODE_OUTPUT_PP;
  PC0.Pull = GPIO_NOPULL;
  PC0.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Config(GPIOC, &PC0);
	
	GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET);
}


void drainValeGpioInit()
{
	GPIO_InitTypeDef PB4_PB5,PD6,PC9 = {0};

	/*Configure GPIO pins : 
	<-> PB4 ---> Valve Open Indication
	<-> PB5 ---> Valve Close Indication
	<-> PD6 ---> Turn On the Valve
	<-> PC9 ---> 
	*/
	
  PB4_PB5.Pin = GPIO_PIN_4|GPIO_PIN_5;
  PB4_PB5.Mode = GPIO_MODE_INPUT;
  PB4_PB5.Pull = GPIO_NOPULL;
  GPIO_Config(GPIOB, &PB4_PB5);
	
	/*Configure GPIO pin Output Level */
	
  GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
	
	PD6.Pin = GPIO_PIN_6;
  PD6.Mode = GPIO_MODE_OUTPUT_PP;
  PD6.Pull = GPIO_NOPULL;
  PD6.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Config(GPIOD, &PD6);
	
	/*Configure GPIO pin Output Level */
  
	GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	
  PC9.Pin = GPIO_PIN_9;
  PC9.Mode = GPIO_MODE_OUTPUT_PP;
  PC9.Pull = GPIO_NOPULL;
  PC9.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Config(GPIOC, &PC9);
}

void vfdGpioInit()
{
	GPIO_InitTypeDef PD4_PD3,PB6_PB7 = {0};
	
	/*Configure GPIO pins : 
	<-> PD4 ---> Forward/ON
	<-> PD3 ---> Reverse
	<-> PB6 ---> FeedBack
	<-> PB7 ---> FaultDectection
	*/
	
	/*Configure GPIO pin Output Level */
  GPIO_WritePin(GPIOD,GPIO_PIN_4|GPIO_PIN_3, GPIO_PIN_RESET);
	
  PD4_PD3.Pin = GPIO_PIN_4|GPIO_PIN_3;
  PD4_PD3.Mode = GPIO_MODE_OUTPUT_PP;
  PD4_PD3.Pull = GPIO_NOPULL;
  PD4_PD3.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_Config(GPIOD, &PD4_PD3);
	
	/*Configure GPIO pins : PB6 PB7 */
  PB6_PB7.Pin = GPIO_PIN_6|GPIO_PIN_7;
  PB6_PB7.Mode = GPIO_MODE_INPUT;
  PB6_PB7.Pull = GPIO_NOPULL;
  GPIO_Config(GPIOB, &PB6_PB7);
}

void proximitySensorInit()
{
	GPIO_InitTypeDef PB3 = {0};
	
	/*Configure GPIO pin : PB3 */
  
	PB3.Pin = GPIO_PIN_3;
  PB3.Mode = GPIO_MODE_INPUT;
  PB3.Pull = GPIO_NOPULL;
  GPIO_Config(GPIOB, &PB3);
}

void OnBoardLedInit()
{
	GPIO_InitTypeDef PC14_PC15 = {0};
	/*Configure GPIO pin Output Level */
  GPIO_WritePin(GPIOC,GPIO_PIN_14, GPIO_PIN_RESET);
	
	/*Configure GPIO pin : PIN*/
	PC14_PC15.Pin = GPIO_PIN_14|GPIO_PIN_15;
	PC14_PC15.Mode = GPIO_MODE_OUTPUT_PP;
	PC14_PC15.Pull = GPIO_NOPULL;
	GPIO_Config(GPIOC, &PC14_PC15);
}


void blueToothPinInit()
{
	GPIO_InitTypeDef PB12,PB11 = {0};
	
	/*Configure GPIO pin : PB12 - BLE State PIN*/
  
	PB12.Pin = GPIO_PIN_12;
  PB12.Mode = GPIO_MODE_INPUT;
  PB12.Pull = GPIO_NOPULL;
  GPIO_Config(GPIOB, &PB12);
	
	/*Configure GPIO pin Output Level */
  GPIO_WritePin(GPIOB,GPIO_PIN_11, GPIO_PIN_RESET);
	
	/*Configure GPIO pin : PB11 - BLE EN PIN*/
	PB11.Pin = GPIO_PIN_11;
	PB11.Mode = GPIO_MODE_OUTPUT_PP;
	PB11.Pull = GPIO_NOPULL;
	GPIO_Config(GPIOB, &PB11);
}

/**********************************************************/
/* HAL IOs Init					                                  */
/**********************************************************/


/*	This Function is called to Initialise the USART Pins  */
static void uart2IoInit(void)
{
  GPIO_InitTypeDef PA = {0};

  /* Pheriperal Clock Enable */
	RCC_USART2_CLK_ENABLE();
	
  /*Configure GPIO pins : PA2 PA3 
	 *	A2--> Tx
	 *	A3--> Rx
	*/
  
	PA.Pin = GPIO_PIN_2|GPIO_PIN_3;
  PA.Mode = GPIO_MODE_AF_PP;
  PA.Pull = GPIO_NOPULL;
  PA.Speed = GPIO_SPEED_FREQ_LOW;
  PA.Alternate = GPIO_AF1_USART2;
  GPIO_Config(GPIOA, &PA);
}

/*	This Function is called to Initialise the USART Pins  */
static void uart1IoInit(void)
{	
	GPIO_InitTypeDef PC;
	
	RCC_USART1_CLK_ENABLE();
	
	/*Configure GPIO pins : PC4 PC5 
	*	PC4--> Tx
	*	PC5--> Rx
	*/
  PC.Pin = GPIO_PIN_4|GPIO_PIN_5;
  PC.Mode = GPIO_MODE_AF_PP;
  PC.Pull = GPIO_NOPULL;
  PC.Speed = GPIO_SPEED_FREQ_LOW;
  PC.Alternate = GPIO_AF1_USART1;
	GPIO_Config(GPIOC,&PC);	
}


static void dacGpioInit(void)
{
	GPIO_InitTypeDef PA,PC = {0};
	
	RCC->APBENR1 |= RCC_APBENR1_DAC1EN; // Clock Enable
	
  /*Configure GPIO pin : PA4 */
  PA.Pin = GPIO_PIN_4;
  PA.Mode = GPIO_MODE_ANALOG;
  PA.Pull = GPIO_NOPULL;
  PA.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_Config(GPIOA, &PA);
}

/**SPI1 GPIO Configuration**/

static void spiGpioInit()
{
	GPIO_InitTypeDef PA,PB = {0};

	/*Configure GPIO pin : 
	PB0			------> TEMP1_CS
	PB1			------> TEMP2_CS
	PB2			------> MCP3008_CS
	*/
	PB.Pin = GPIO_PIN_0| GPIO_PIN_1 | GPIO_PIN_2;
	PB.Mode = GPIO_MODE_OUTPUT_PP;
	PB.Pull = GPIO_NOPULL;
	PB.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_Config(GPIOB, &PB);

	/**SPI1 GPIO Configuration
	PA5     ------> SPI1_SCK
	PA6     ------> SPI1_MISO
	PA7     ------> SPI1_MOSI
	*/
	PA.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	PA.Mode = GPIO_MODE_AF_PP;
	PA.Pull = GPIO_NOPULL;
	PA.Speed = GPIO_SPEED_FREQ_LOW;
	PA.Alternate = GPIO_AF0_SPI1;
	GPIO_Config(GPIOA, &PA);

	GPIO_WritePin(GPIOB,GPIO_PIN_0,1);
}


void gpioInit()
{

	gpioClockEnable(); // Clock Enable For All IOs
	OnBoardLedInit();
	blueToothPinInit();
	outputControls();
	drainValeGpioInit();
	vfdGpioInit();
	proximitySensorInit();
	
	/*Drivers IO init*/
	uart1IoInit();
	uart2IoInit();
	dacGpioInit();
	spiGpioInit();
}
