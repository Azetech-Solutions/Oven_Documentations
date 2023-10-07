#include "Includes.h"
#include "DAC.h"
#include UART_H
#include DEBUG_H

UBYTE DAC_RxValue=0;
UWORD DAC_CalculatedValue=0;
UBYTE PrevDACValue=0;

void DAC_Input(unsigned short int InputDACdata);

void dacInit(void)
{
	/*!<DAC channel1 Disable */
	DAC->CR 	&= ~DAC_CR_EN1;
	
	/* DAC channel1 Trigger Disable */
	DAC->CR 	&= ~DAC_CR_TEN1;
	
	/* SWTRIG1 */
	DAC->CR 	&= ~DAC_CR_TSEL1;
	
	/* DAC channel1 in Normal operating mode */
	DAC->CR 	&= ~DAC_CR_CEN1;
	
	/* DAC channel1 is connected to external pin with Buffer enabled */
	DAC->MCR 	&= ~DAC_MCR_MODE1;
	
	/*!<DAC channel1 enable */
	DAC->CR 	|= DAC_CR_EN1;
}


/*!<
>DAC_Input Function is Used to Update the 12 bit DAC Value In between 1 - 4095.
>Based on this value the voltage will updated in DAC Output pin
*/

void DAC_Input(unsigned short int InputDACdata)
{
	DAC->DHR12R1 = (DAC_DHR12R1_DACC1DHR & InputDACdata)>>0;
	
	DAC->SWTRIGR = DAC_SWTRIGR_SWTRIG1;
	
	while(DAC->SWTRIGR & DAC_SWTRIGR_SWTRIG1);
}


