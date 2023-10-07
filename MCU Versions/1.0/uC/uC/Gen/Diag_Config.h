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

#ifndef __DIAG_CONFIG_H__
#define __DIAG_CONFIG_H__

#include "Platform_Types.h"

/*************************************************/
/* Functional Switches and Parameter Definitions */
/*************************************************/


/*************************************************/
/*          Diagnostics Events List IDs          */
/*************************************************/

#define DiagEvent_CookingConfig_Error               0u
#define DiagEvent_Wash_Error               1u
#define DiagEvent_Heater_Error               2u
#define DiagEvent_DrainValve_Error               3u
#define DiagEvent_Motor_Error               4u
#define DiagEvent_Steam_Error               5u
#define DiagEvent_HMI_ComIf_Error               6u
#define DiagEvent_Sensor_Error               7u
#define DiagEvent_Synchronization_Error               8u

#define DiagEvent_COUNT                         9u

/* Macro to create a bit wise byte array for the application layer */
#define DiagEventStatusByteLength               2u

/*************************************************/
/*         Diagnostics Filter Definitions        */
/*************************************************/

/* Filter ID and Mask definition for  */
#define DiagFilter_             0u
#define DiagFilter_Mask_        1u


/*************************************************/
/*               Macro Definitions               */
/*************************************************/

#define Diag_IsFailed_CookingConfig_Error()         (DiagEventStatus[DiagEvent_CookingConfig_Error].IsFailed == TRUE)
#define Diag_IsFailed_Wash_Error()         (DiagEventStatus[DiagEvent_Wash_Error].IsFailed == TRUE)
#define Diag_IsFailed_Heater_Error()         (DiagEventStatus[DiagEvent_Heater_Error].IsFailed == TRUE)
#define Diag_IsFailed_DrainValve_Error()         (DiagEventStatus[DiagEvent_DrainValve_Error].IsFailed == TRUE)
#define Diag_IsFailed_Motor_Error()         (DiagEventStatus[DiagEvent_Motor_Error].IsFailed == TRUE)
#define Diag_IsFailed_Steam_Error()         (DiagEventStatus[DiagEvent_Steam_Error].IsFailed == TRUE)
#define Diag_IsFailed_HMI_ComIf_Error()         (DiagEventStatus[DiagEvent_HMI_ComIf_Error].IsFailed == TRUE)
#define Diag_IsFailed_Sensor_Error()         (DiagEventStatus[DiagEvent_Sensor_Error].IsFailed == TRUE)
#define Diag_IsFailed_Synchronization_Error()         (DiagEventStatus[DiagEvent_Synchronization_Error].IsFailed == TRUE)

/* Power Cycle Count maximum is UWORD - 16 bits */
#define DIAG_MAX_POWER_CYCLE_COUNT              ( 65535U )

/* Maximum Failure logged counter is UWORD - 16 bits */
#define DIAG_MAX_FAILURE_COUNT                  ( 65535U )

/* Diag filter APIs */

/* Filter APIs for  */
#define Diag_ActivateFilter_()             (DiagActiveFilter |= DiagFilter_Mask_)
#define Diag_DeactivateFilter_()           (DiagActiveFilter &= (~DiagFilter_Mask_))
#define Diag_IsFilterActive_()             (DiagActiveFilter & DiagFilter_Mask_ != 0)

#define DIAG_MAX_FILTER_COUNT                   1u

/*************************************************/
/*               Type Definitions                */
/*************************************************/
typedef union __DiagFlags_t
{
    struct {
        /* This structure must not exceed 8 bits */
        
        /* Status Bits */
        UBYTE IsFailed      : 1; // If set, then the Diagnostics Event has been failed
        UBYTE IsNewInstance : 1; // If set, then there is a new instance of the failure has been reported
        UBYTE IsFiltered    : 1; // If set, then the event is filtered because of system conditions
    };
    UBYTE Flags;
}DiagFlags_t;

typedef UBYTE DiagEventFilter_t;

/*************************************************/
/*               Global Variables                */
/*************************************************/

extern DiagFlags_t DiagEventStatus[];
extern DiagEventFilter_t DiagEventFilter[];
extern DiagEventFilter_t DiagActiveFilter;

/*************************************************/
/*          Extern Function Declarations         */
/*************************************************/

extern void Diag_Config_Init(void);

#endif /* __DIAG_CONFIG_H__ */

