/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "flowSensor.h"
#include DEBUG_H
#include COMIF_H
#include DIAG_H
#include COOKING_H
#include DIAGIDS_H
#include WASH_H
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
flowSenor_ST CH1;

ULONG CaptureMillis = 0;
ULONG Millis = 0;

ULONG MLResetCount = 0;
ULONG FlowTimoutCounter = 0;
ULONG NoWaterIndicatorCount = 0;
ULONG WaterInletOffIndicateCounter = 0;
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define FLOWRATE_MULTIPLICATION_FACTOR 				10
#define FLOWRATE_LM_TO_MLM_CONVERTION_FACTOR 				1000
/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

static uint32_t getCapturedValue(TIM_TypeDef *timer, uint32_t channel);

void ConfigureInputCapture(TIM_TypeDef *timer);


/*<!
	*	TIM1_CC_IRQHandler is a ISR this ISR will Called when Timer overflow or Capture interrupt Occurs
	* This ISR is used to measure the number of pulses of flowsensor 
	* Millis is used to hold the accurate time it stores the timer value from the begining in Milli second Resolution
	* In this ISR the Start time and end time of the Flowsensor pulses will be calculated and the number of pulses will
		counted in CH1.freqencyCounter variable
>*/

void TIM1_CC_IRQHandler(void)
{	
	
	if(TIM1->SR & TIM_SR_UIF)
	{
		Millis += 65000;
		
		TIM1->SR &= ~TIM_SR_UIF;
	}
	
	if(TIM1->SR & TIM_SR_CC1IF)
	{		
		CaptureMillis = (Millis + getCapturedValue(TIM1, 1));
		
		//practically calibrated value 2ml/pulse 
		CH1.volume += 2 ;

		if(CH1.StartTimeStamp == 0)
		{
			CH1.StartTimeStamp = CaptureMillis;
		}
		
		CH1.EndTimeStamp = CaptureMillis;
		
		CH1.freqencyCounter++;
		
		TIM1->SR &= ~TIM_SR_CC1IF;
		
		if(TIM1->SR & TIM_SR_CC1OF)
		{
			TIM1->SR &=	~TIM_SR_CC1OF;
		}
	}
	
}


void inputCaptureInit()
{
	GPIO_InitTypeDef PA = {0};

  /* GPIO Ports Clock Enable */
  PORTA_CLOCK_ENABLE();

  /*Configure GPIO pins : PA8 PA9 PA10 */
  PA.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 ;
  PA.Mode = GPIO_MODE_AF_PP;
  PA.Pull = GPIO_NOPULL;
  PA.Speed = GPIO_SPEED_FREQ_LOW;
  PA.Alternate = GPIO_AF2_TIM1;
  GPIO_Config(GPIOA, &PA);
}

void ConfigureInputCapture(TIM_TypeDef *timer)
{
	/*Enable the clock for the timer peripheral*/
	RCC->APBENR2 	|= RCC_APBENR2_TIM1EN;

	/*Select Input Channel*/
	timer->TISEL 	&= ~TIM_TISEL_TI1SEL;
	timer->TISEL 	&= ~TIM_TISEL_TI2SEL;
	timer->TISEL 	&= ~TIM_TISEL_TI3SEL;
	/**************Channel 1********************/
	timer->DIER = 0x0000;
	
	/*Set the input capture channel to be used*/
	
	timer->CCMR1 	&= ~TIM_CCMR1_CC1S; // reset
	timer->CCMR1 	|= TIM_CCMR1_CC1S_0; // // 01: CC1 channel is configured as input, IC2 is mapped on TI1 (TI1-Internal Clock)
	timer->CCMR1 	&= ~TIM_CCMR1_IC1PSC; // 00: no prescaler, capture is done each time an edge is detected on the capture input
	timer->CCMR1 	&= ~TIM_CCMR1_IC1F; //Clear the bits
	timer->CCMR1 	|=  TIM_CCMR1_IC1F_0 | TIM_CCMR1_IC1F_2; // 0101: fSAMPLING=fDTS/2, N=8

	/*Enable input capture on the selected channel*/
	
	/*CC1NP=0, CC1P=0: non-inverted/rising edge. */
	timer->CCER 	&= ~TIM_CCER_CC1P;
	timer->CCER 	&= ~TIM_CCER_CC1NP;

	timer->CCER 	|= TIM_CCER_CC1E;//1: Capture mode enabled / OC1 signal is output on the corresponding output pin
	timer->DIER 	|= TIM_DIER_CC1IE; 
	
	timer->DIER 	|= TIM_DIER_UIE; // Update interrupt enable 
	
	/*Enable the timer counter*/
	
	timer->ARR 		 = 65000;
	timer->PSC 		 = 64000;

	timer->CR1 		|= TIM_CR1_CEN;
	timer->CR1		|= TIM_CR1_ARPE;

	timer->SR = 0x00000000;

	NVIC_EnableIRQ(TIM1_CC_IRQn);
}

uint32_t getCapturedValue(TIM_TypeDef *timer, uint32_t channel)
{
    uint32_t capturedValue = 0;

    if (channel == 1)
    {
        capturedValue = timer->CCR1;
    }
    else if (channel == 2)
    {
        capturedValue = timer->CCR2;
    }
    else if (channel == 3)
    {
        capturedValue = timer->CCR3;
    }
		
    return capturedValue;
}

void flowSensorInit()
{
	inputCaptureInit();
	ConfigureInputCapture(TIM1);
}

/*<!
	* The calculateFlowRate() function is used to calculate the current flow rate of the water.
	* It is called in 10 ms task but whenever the value frequency counter is greater than 1 
		then only the calculation proceded.
	*
>*/

void calculateFlowRate()
{
	machineStatus_ST *MachineStatus = &machineStatus;
	
	ULONG TotalRunTime;
	ULONG FrequencyCounter = 0;
	
	if(CH1.freqencyCounter > 1)
	{
		NVIC_DisableIRQ(TIM1_CC_IRQn);
		
		TotalRunTime = CH1.EndTimeStamp - CH1.StartTimeStamp;
		
		FrequencyCounter = CH1.freqencyCounter;
		
		if(TotalRunTime < 300)
		{
			CH1.StartTimeStamp = 0;
			CH1.EndTimeStamp = 0;
			CH1.freqencyCounter = 0;
		}
		else
		{
			CH1.StartTimeStamp = CH1.EndTimeStamp;
			CH1.EndTimeStamp = 0;
			CH1.freqencyCounter = 0;
		}
		
		NVIC_EnableIRQ(TIM1_CC_IRQn);
		
		CH1.freqency = (UL)(((FrequencyCounter * 1000)/TotalRunTime) + 0.5);
		
		CH1.MLPerMinute = (UL)((((CH1.freqency+5)*FLOWRATE_MULTIPLICATION_FACTOR)/81)*FLOWRATE_LM_TO_MLM_CONVERTION_FACTOR);
	}
	else
	{
		CH1.MLPerMinute = 0;
	}
		
	//Check the water inlet valve is open or not
	if(IsWaterInletOpenFlag == TRUE)
	{
		if(CH1.MLPerMinute < 500)
		{
			NoWaterIndicatorCount++;
			//wait for 3s to flow water if not then lock the error and pause the state
			if(NoWaterIndicatorCount > 300)
			{
				MachineStatus->NWF = TRUE;
				
				Send_MachineStatus();
				
				Diag_ReportEvent(DiagEvent_Steam_Error,STEAM_NOT_WORKING,CH1.MLPerMinute);
				
				if(washState != WS_Idle)
				{
					washState = WS_NoWaterPause;
					
					steamControl = E_steamIdle;
				}
				
				if(IsCookingProgress())
				{
					PauseTheCooking();
					NoWaterIndicatorCount = 0;
					steamControl = E_steamIdle;
				}
				
				NoWaterIndicatorCount = 0;
			}
		}
		else
		{
			NoWaterIndicatorCount = 0;
			MachineStatus->NWF = FALSE;
		}
	}
	else
	{
		WaterInletOffIndicateCounter++;
		
		if(WaterInletOffIndicateCounter > 250)
		{
			if(CH1.MLPerMinute > 400 )
			{
				Debug_SendString("WaterNotstoped\n");
				//report error steam not turning off
				Diag_ReportEvent(DiagEvent_Steam_Error,STEAM_NOT_TURNING_OFF,CH1.MLPerMinute);
			}
			
			WaterInletOffIndicateCounter = 0;
		}
	}
}


void flowSensorMain()
{
	if(CH1.volume > 0)
	{
		UBYTE *Data = ComIf_GetShadowBuffer_HMI_waterConsumptionStatus();
		
		/*****Sensor 1 Comif Tx Data*****/	
		Data[0] = (UB) (((CH1.volume & 0x00FF0000)  >> 16)) ;//Flow Rate MSB
		
		Data[1] = (UB) (((CH1.volume & 0x0000FF00)  >> 8)) ;//Flow Rate LSB
		
		Data[2] = (UB) (((CH1.volume & 0x000000FF))) ; //Store the MSB of the Total Water Volume Level
		
		ComIf_TransmitFromBuffer_HMI_waterConsumptionStatus();
	}

	CH1.volume = 0;
}
