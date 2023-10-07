#include "Includes.h"
#include "stm32g0xx.h"                  // Device header
#include "WDG.h"
#include DEBUG_H
#include "stdio.h"

/*
tWWDG = tPCLK x 4096 x 2^WDGTB[1:0] x (T [5:0] + 1) (ms)

tWWDG = (1/16000000) x (4096 x (2^2)) x (195 + 1)
*/

void WWDG_Init(void)
{
	RCC->APBENR1 	|= 	RCC_APBENR1_WWDGEN;

	WWDG->CR 			&= 0x00000000; //rst

	WWDG->CR		 	|= (109 << WWDG_CR_T_Pos);

	WWDG->CFR 		&= 0x00000000; //rst

	WWDG->CFR			|= WWDG_CFR_WDGTB_2;

	WWDG->CFR		 	|= (109 << WWDG_CFR_W_Pos);

	WWDG->CR 		 	|=	WWDG_CR_WDGA; // Watchdog enabled
}

/*This function used to trigger within 1ms to 50ms,otherwise WDT reset microcontroller */

void WDG_Sync(void)
{
	WWDG->CR	= (109 << WWDG_CR_T_Pos);
}
