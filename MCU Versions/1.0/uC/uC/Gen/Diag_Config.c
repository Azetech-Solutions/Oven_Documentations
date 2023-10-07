/******************************************************************
                A Z E T E C H    S O L U T I O N S                 
-------------------------------------------------------------------
        T O O L   G E N E R A T E D   S O U R C E   C O D E        
                    D O   N O T   M O D I F Y                      
-------------------------------------------------------------------
 This file is generated with the Azetech copyrighted software tool 
 No modification should be done in this file without a written     
 consent from Azetech Solutions. Incase of any such instances,     
 Azetech Solutions will not be liable to any damages it cause.     
-------------------------------------------------------------------
 Any Distribution, Alteration, Removal, Disassemble, Decompile or  
 or Reverse Engineer the given software, without written consent   
 from Azetech Solutions by the Licensee or third parties were not  
 allowed. Such instance is considered as a breach and the Licensee 
 is the sole responsible and liable to any damages it cause.       
******************************************************************/

#include "Includes.h"
#include DIAG_H

/******************************************************/
/*           Global Variable Definitions              */
/******************************************************/

// Clear all the flags by default
DiagFlags_t DiagEventStatus[DiagEvent_COUNT] = {0};

// Initialize Filter Variable
DiagEventFilter_t DiagActiveFilter = 0;

// Initialize the Diag Filters based on the Mask configured
DiagEventFilter_t DiagEventFilter[DiagEvent_COUNT] = 
{
    /* CookingConfig_Error */         ( 0 ),
    /* Wash_Error */         ( 0 ),
    /* Heater_Error */         ( 0 ),
    /* DrainValve_Error */         ( 0 ),
    /* Motor_Error */         ( 0 ),
    /* Steam_Error */         ( 0 ),
    /* HMI_ComIf_Error */         ( 0 ),
    /* Sensor_Error */         ( 0 ),
    /* Synchronization_Error */         ( 0 ),
};

/***************************************************/
/* Function Definitions                            */
/***************************************************/
void Diag_Config_Init(void)
{
    DiagActiveFilter = 0;

    for(int i = 0; i < DiagEvent_COUNT; i++)
	{
		DiagEventStatus[i].Flags=0;
	}
}

