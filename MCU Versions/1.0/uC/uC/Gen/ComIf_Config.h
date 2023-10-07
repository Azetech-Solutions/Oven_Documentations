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

#ifndef __COMIF_CONFIG_H__
#define __COMIF_CONFIG_H__

#include "Platform_Types.h"
#include "ComIf_Config_Elements.h"

/*************************************************/
/* Functional Switches and Parameter Definitions */
/*************************************************/

/* Invalid Index handle */
#define P_COMIF_INVALID_HANDLE                255u

/* ComIf Input Method */
#define S_COMIF_INPUT_METHOD                  COMIF_INPUT_METHOD_INTERRUPT

#define COMIF_MAX_SUPPORTED_DLC               255 // 255 Bytes

#define COMIF_MAX_SUPPORTED_CHKLEN            1   // 1 Byte

#define COMIF_TX_MAIN_FUNCTION_PERIOD         10

#define COMIF_RX_MAIN_FUNCTION_PERIOD         10

/*************************************************/
/*               Macro Definitions               */
/*************************************************/

#if COMIF_MAX_SUPPORTED_DLC < 64
#error "The channel HMI has more data length in the dynamic section than the supported DLC"
#endif

/* Transmit Message constants for the channel : HMI */
#define P_COMIF_TXBUFFER_SIZE_HMI                    256u

/* Constants for the Tx message machineStatus on HMI channel */

#define ComIf_GetIndex_HMI_machineStatus()                   (0u)
#define ComIf_GetLength_HMI_machineStatus()                  (1u)
#define ComIf_GetShadowBuffer_HMI_machineStatus()            ((UBYTE *)ComIf_ShadowBuffer_HMI_machineStatus)
#define ComIf_Transmit_HMI_machineStatus(x, y)               ComIf_Transmit(C_ComIfChannel_HMI, 0, ((void *)x), y)
#define ComIf_ForceTransmit_HMI_machineStatus(x, y)          do{ComIfTxMsgCfg_HMI[0].TxFlags.ForceTransmit = TRUE; ComIf_Transmit(C_ComIfChannel_HMI, 0, ((void *)x), y); } while(0)
#define ComIf_UpdateTxShadowBuffer_HMI_machineStatus(x, y)   ComIf_UpdateTxShadowBuffer(C_ComIfChannel_HMI, 0, ((void *)x), y)
#define ComIf_TransmitFromBuffer_HMI_machineStatus()         ComIf_Transmit_HMI_machineStatus(ComIf_ShadowBuffer_HMI_machineStatus, 1)
#define ComIf_ForceTransmitFromBuffer_HMI_machineStatus()    ComIf_ForceTransmit_HMI_machineStatus(ComIf_ShadowBuffer_HMI_machineStatus, 1)

/* Debug Measurement Variables for machineStatus on HMI */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[0].TxFlags.PendingForTransmission */
/* MODELNAME=ComIfTxMsgCfg_HMI_machineStatus_PendingForTransmission */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[0].TxFlags.PendingForConfirmation */
/* MODELNAME=ComIfTxMsgCfg_HMI_machineStatus_PendingForConfirmation */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[0].TxFlags.AggregatedInBuffer */
/* MODELNAME=ComIfTxMsgCfg_HMI_machineStatus_AggregatedInBuffer */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */


/* Constants for the Tx message sensorData on HMI channel */

#define ComIf_GetIndex_HMI_sensorData()                   (1u)
#define ComIf_GetLength_HMI_sensorData()                  (8u)
#define ComIf_GetShadowBuffer_HMI_sensorData()            ((UBYTE *)ComIf_ShadowBuffer_HMI_sensorData)
#define ComIf_Transmit_HMI_sensorData(x, y)               ComIf_Transmit(C_ComIfChannel_HMI, 1, ((void *)x), y)
#define ComIf_ForceTransmit_HMI_sensorData(x, y)          do{ComIfTxMsgCfg_HMI[1].TxFlags.ForceTransmit = TRUE; ComIf_Transmit(C_ComIfChannel_HMI, 1, ((void *)x), y); } while(0)
#define ComIf_UpdateTxShadowBuffer_HMI_sensorData(x, y)   ComIf_UpdateTxShadowBuffer(C_ComIfChannel_HMI, 1, ((void *)x), y)
#define ComIf_TransmitFromBuffer_HMI_sensorData()         ComIf_Transmit_HMI_sensorData(ComIf_ShadowBuffer_HMI_sensorData, 8)
#define ComIf_ForceTransmitFromBuffer_HMI_sensorData()    ComIf_ForceTransmit_HMI_sensorData(ComIf_ShadowBuffer_HMI_sensorData, 8)

/* Debug Measurement Variables for sensorData on HMI */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[1].TxFlags.PendingForTransmission */
/* MODELNAME=ComIfTxMsgCfg_HMI_sensorData_PendingForTransmission */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[1].TxFlags.PendingForConfirmation */
/* MODELNAME=ComIfTxMsgCfg_HMI_sensorData_PendingForConfirmation */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[1].TxFlags.AggregatedInBuffer */
/* MODELNAME=ComIfTxMsgCfg_HMI_sensorData_AggregatedInBuffer */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */


/* Constants for the Tx message waterConsumptionStatus on HMI channel */

#define ComIf_GetIndex_HMI_waterConsumptionStatus()                   (2u)
#define ComIf_GetLength_HMI_waterConsumptionStatus()                  (3u)
#define ComIf_GetShadowBuffer_HMI_waterConsumptionStatus()            ((UBYTE *)ComIf_ShadowBuffer_HMI_waterConsumptionStatus)
#define ComIf_Transmit_HMI_waterConsumptionStatus(x, y)               ComIf_Transmit(C_ComIfChannel_HMI, 2, ((void *)x), y)
#define ComIf_ForceTransmit_HMI_waterConsumptionStatus(x, y)          do{ComIfTxMsgCfg_HMI[2].TxFlags.ForceTransmit = TRUE; ComIf_Transmit(C_ComIfChannel_HMI, 2, ((void *)x), y); } while(0)
#define ComIf_UpdateTxShadowBuffer_HMI_waterConsumptionStatus(x, y)   ComIf_UpdateTxShadowBuffer(C_ComIfChannel_HMI, 2, ((void *)x), y)
#define ComIf_TransmitFromBuffer_HMI_waterConsumptionStatus()         ComIf_Transmit_HMI_waterConsumptionStatus(ComIf_ShadowBuffer_HMI_waterConsumptionStatus, 3)
#define ComIf_ForceTransmitFromBuffer_HMI_waterConsumptionStatus()    ComIf_ForceTransmit_HMI_waterConsumptionStatus(ComIf_ShadowBuffer_HMI_waterConsumptionStatus, 3)

/* Debug Measurement Variables for waterConsumptionStatus on HMI */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[2].TxFlags.PendingForTransmission */
/* MODELNAME=ComIfTxMsgCfg_HMI_waterConsumptionStatus_PendingForTransmission */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[2].TxFlags.PendingForConfirmation */
/* MODELNAME=ComIfTxMsgCfg_HMI_waterConsumptionStatus_PendingForConfirmation */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[2].TxFlags.AggregatedInBuffer */
/* MODELNAME=ComIfTxMsgCfg_HMI_waterConsumptionStatus_AggregatedInBuffer */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */


/* Constants for the Tx message ErrorData on HMI channel */

#define ComIf_GetIndex_HMI_ErrorData()                   (3u)
#define ComIf_GetLength_HMI_ErrorData()                  (9u)
#define ComIf_GetShadowBuffer_HMI_ErrorData()            ((UBYTE *)ComIf_ShadowBuffer_HMI_ErrorData)
#define ComIf_Transmit_HMI_ErrorData(x, y)               ComIf_Transmit(C_ComIfChannel_HMI, 3, ((void *)x), y)
#define ComIf_ForceTransmit_HMI_ErrorData(x, y)          do{ComIfTxMsgCfg_HMI[3].TxFlags.ForceTransmit = TRUE; ComIf_Transmit(C_ComIfChannel_HMI, 3, ((void *)x), y); } while(0)
#define ComIf_UpdateTxShadowBuffer_HMI_ErrorData(x, y)   ComIf_UpdateTxShadowBuffer(C_ComIfChannel_HMI, 3, ((void *)x), y)
#define ComIf_TransmitFromBuffer_HMI_ErrorData()         ComIf_Transmit_HMI_ErrorData(ComIf_ShadowBuffer_HMI_ErrorData, 9)
#define ComIf_ForceTransmitFromBuffer_HMI_ErrorData()    ComIf_ForceTransmit_HMI_ErrorData(ComIf_ShadowBuffer_HMI_ErrorData, 9)

/* Debug Measurement Variables for ErrorData on HMI */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[3].TxFlags.PendingForTransmission */
/* MODELNAME=ComIfTxMsgCfg_HMI_ErrorData_PendingForTransmission */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[3].TxFlags.PendingForConfirmation */
/* MODELNAME=ComIfTxMsgCfg_HMI_ErrorData_PendingForConfirmation */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[3].TxFlags.AggregatedInBuffer */
/* MODELNAME=ComIfTxMsgCfg_HMI_ErrorData_AggregatedInBuffer */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */


/* Constants for the Tx message diagnosticData on HMI channel */

#define ComIf_GetIndex_HMI_diagnosticData()                   (4u)
#define ComIf_GetLength_HMI_diagnosticData()                  (1u)
#define ComIf_GetShadowBuffer_HMI_diagnosticData()            ((UBYTE *)ComIf_ShadowBuffer_HMI_diagnosticData)
#define ComIf_Transmit_HMI_diagnosticData(x, y)               ComIf_Transmit(C_ComIfChannel_HMI, 4, ((void *)x), y)
#define ComIf_ForceTransmit_HMI_diagnosticData(x, y)          do{ComIfTxMsgCfg_HMI[4].TxFlags.ForceTransmit = TRUE; ComIf_Transmit(C_ComIfChannel_HMI, 4, ((void *)x), y); } while(0)
#define ComIf_UpdateTxShadowBuffer_HMI_diagnosticData(x, y)   ComIf_UpdateTxShadowBuffer(C_ComIfChannel_HMI, 4, ((void *)x), y)
#define ComIf_TransmitFromBuffer_HMI_diagnosticData()         ComIf_Transmit_HMI_diagnosticData(ComIf_ShadowBuffer_HMI_diagnosticData, 1)
#define ComIf_ForceTransmitFromBuffer_HMI_diagnosticData()    ComIf_ForceTransmit_HMI_diagnosticData(ComIf_ShadowBuffer_HMI_diagnosticData, 1)

/* Debug Measurement Variables for diagnosticData on HMI */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[4].TxFlags.PendingForTransmission */
/* MODELNAME=ComIfTxMsgCfg_HMI_diagnosticData_PendingForTransmission */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[4].TxFlags.PendingForConfirmation */
/* MODELNAME=ComIfTxMsgCfg_HMI_diagnosticData_PendingForConfirmation */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */

/* [[DEBUG_MEASUREMENT */
/* NAME=ComIfTxMsgCfg_HMI[4].TxFlags.AggregatedInBuffer */
/* MODELNAME=ComIfTxMsgCfg_HMI_diagnosticData_AggregatedInBuffer */
/* SIZE=1 */
/* HEADER=ComIf_Config.h */
/* DEBUG_MEASUREMENT]] */


/* Receive Message constants for the channel : HMI */

/* Constants for the Rx message androidData on HMI channel */

#define ComIf_GetIndex_HMI_androidData()                   (0u)
#define ComIf_GetLength_HMI_androidData()                  (2u)
#define ComIf_GetBuffer_HMI_androidData()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_androidData)
#define ComIf_GetRxFlags_HMI_androidData()                 (ComIfRxMsgCfg_HMI[0].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_androidData()       ((ComIfRxMsgCfg_HMI[0].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[0].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_androidData() (ComIfRxMsgCfg_HMI[0].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_androidData()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[0].RxFlags))

/* Constants for the Rx message recipeStepConfiguration on HMI channel */

#define ComIf_GetIndex_HMI_recipeStepConfiguration()                   (1u)
#define ComIf_GetLength_HMI_recipeStepConfiguration()                  (1u)
#define ComIf_GetBuffer_HMI_recipeStepConfiguration()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_recipeStepConfiguration)
#define ComIf_GetRxFlags_HMI_recipeStepConfiguration()                 (ComIfRxMsgCfg_HMI[1].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_recipeStepConfiguration()       ((ComIfRxMsgCfg_HMI[1].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[1].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_recipeStepConfiguration() (ComIfRxMsgCfg_HMI[1].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_recipeStepConfiguration()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[1].RxFlags))

/* Constants for the Rx message recipeStep1 on HMI channel */

#define ComIf_GetIndex_HMI_recipeStep1()                   (2u)
#define ComIf_GetLength_HMI_recipeStep1()                  (4u)
#define ComIf_GetBuffer_HMI_recipeStep1()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_recipeStep1)
#define ComIf_GetRxFlags_HMI_recipeStep1()                 (ComIfRxMsgCfg_HMI[2].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_recipeStep1()       ((ComIfRxMsgCfg_HMI[2].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[2].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_recipeStep1() (ComIfRxMsgCfg_HMI[2].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_recipeStep1()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[2].RxFlags))

/* Constants for the Rx message recipeStep2 on HMI channel */

#define ComIf_GetIndex_HMI_recipeStep2()                   (3u)
#define ComIf_GetLength_HMI_recipeStep2()                  (4u)
#define ComIf_GetBuffer_HMI_recipeStep2()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_recipeStep2)
#define ComIf_GetRxFlags_HMI_recipeStep2()                 (ComIfRxMsgCfg_HMI[3].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_recipeStep2()       ((ComIfRxMsgCfg_HMI[3].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[3].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_recipeStep2() (ComIfRxMsgCfg_HMI[3].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_recipeStep2()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[3].RxFlags))

/* Constants for the Rx message recipeStep3 on HMI channel */

#define ComIf_GetIndex_HMI_recipeStep3()                   (4u)
#define ComIf_GetLength_HMI_recipeStep3()                  (4u)
#define ComIf_GetBuffer_HMI_recipeStep3()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_recipeStep3)
#define ComIf_GetRxFlags_HMI_recipeStep3()                 (ComIfRxMsgCfg_HMI[4].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_recipeStep3()       ((ComIfRxMsgCfg_HMI[4].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[4].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_recipeStep3() (ComIfRxMsgCfg_HMI[4].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_recipeStep3()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[4].RxFlags))

/* Constants for the Rx message recipeStep4 on HMI channel */

#define ComIf_GetIndex_HMI_recipeStep4()                   (5u)
#define ComIf_GetLength_HMI_recipeStep4()                  (4u)
#define ComIf_GetBuffer_HMI_recipeStep4()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_recipeStep4)
#define ComIf_GetRxFlags_HMI_recipeStep4()                 (ComIfRxMsgCfg_HMI[5].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_recipeStep4()       ((ComIfRxMsgCfg_HMI[5].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[5].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_recipeStep4() (ComIfRxMsgCfg_HMI[5].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_recipeStep4()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[5].RxFlags))

/* Constants for the Rx message recipeStep5 on HMI channel */

#define ComIf_GetIndex_HMI_recipeStep5()                   (6u)
#define ComIf_GetLength_HMI_recipeStep5()                  (4u)
#define ComIf_GetBuffer_HMI_recipeStep5()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_recipeStep5)
#define ComIf_GetRxFlags_HMI_recipeStep5()                 (ComIfRxMsgCfg_HMI[6].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_recipeStep5()       ((ComIfRxMsgCfg_HMI[6].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[6].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_recipeStep5() (ComIfRxMsgCfg_HMI[6].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_recipeStep5()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[6].RxFlags))

/* Constants for the Rx message recipeStep6 on HMI channel */

#define ComIf_GetIndex_HMI_recipeStep6()                   (7u)
#define ComIf_GetLength_HMI_recipeStep6()                  (4u)
#define ComIf_GetBuffer_HMI_recipeStep6()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_recipeStep6)
#define ComIf_GetRxFlags_HMI_recipeStep6()                 (ComIfRxMsgCfg_HMI[7].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_recipeStep6()       ((ComIfRxMsgCfg_HMI[7].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[7].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_recipeStep6() (ComIfRxMsgCfg_HMI[7].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_recipeStep6()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[7].RxFlags))

/* Constants for the Rx message combiRecipeSettings on HMI channel */

#define ComIf_GetIndex_HMI_combiRecipeSettings()                   (8u)
#define ComIf_GetLength_HMI_combiRecipeSettings()                  (9u)
#define ComIf_GetBuffer_HMI_combiRecipeSettings()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_combiRecipeSettings)
#define ComIf_GetRxFlags_HMI_combiRecipeSettings()                 (ComIfRxMsgCfg_HMI[8].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_combiRecipeSettings()       ((ComIfRxMsgCfg_HMI[8].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[8].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_combiRecipeSettings() (ComIfRxMsgCfg_HMI[8].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_combiRecipeSettings()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[8].RxFlags))

/* Constants for the Rx message steamRecipeSettings on HMI channel */

#define ComIf_GetIndex_HMI_steamRecipeSettings()                   (9u)
#define ComIf_GetLength_HMI_steamRecipeSettings()                  (9u)
#define ComIf_GetBuffer_HMI_steamRecipeSettings()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_steamRecipeSettings)
#define ComIf_GetRxFlags_HMI_steamRecipeSettings()                 (ComIfRxMsgCfg_HMI[9].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_steamRecipeSettings()       ((ComIfRxMsgCfg_HMI[9].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[9].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_steamRecipeSettings() (ComIfRxMsgCfg_HMI[9].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_steamRecipeSettings()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[9].RxFlags))

/* Constants for the Rx message bakingRecipeSettings on HMI channel */

#define ComIf_GetIndex_HMI_bakingRecipeSettings()                   (10u)
#define ComIf_GetLength_HMI_bakingRecipeSettings()                  (4u)
#define ComIf_GetBuffer_HMI_bakingRecipeSettings()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_bakingRecipeSettings)
#define ComIf_GetRxFlags_HMI_bakingRecipeSettings()                 (ComIfRxMsgCfg_HMI[10].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_bakingRecipeSettings()       ((ComIfRxMsgCfg_HMI[10].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[10].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_bakingRecipeSettings() (ComIfRxMsgCfg_HMI[10].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_bakingRecipeSettings()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[10].RxFlags))

/* Constants for the Rx message washSettings on HMI channel */

#define ComIf_GetIndex_HMI_washSettings()                   (11u)
#define ComIf_GetLength_HMI_washSettings()                  (6u)
#define ComIf_GetBuffer_HMI_washSettings()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_washSettings)
#define ComIf_GetRxFlags_HMI_washSettings()                 (ComIfRxMsgCfg_HMI[11].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_washSettings()       ((ComIfRxMsgCfg_HMI[11].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[11].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_washSettings() (ComIfRxMsgCfg_HMI[11].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_washSettings()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[11].RxFlags))

/* Constants for the Rx message diagnosticCommand on HMI channel */

#define ComIf_GetIndex_HMI_diagnosticCommand()                   (12u)
#define ComIf_GetLength_HMI_diagnosticCommand()                  (1u)
#define ComIf_GetBuffer_HMI_diagnosticCommand()                  ((UBYTE *)ComIf_RxMessageBuffer_HMI_diagnosticCommand)
#define ComIf_GetRxFlags_HMI_diagnosticCommand()                 (ComIfRxMsgCfg_HMI[12].RxFlags)
#define ComIf_IsNewMessageReceived_HMI_diagnosticCommand()       ((ComIfRxMsgCfg_HMI[12].RxFlags.NewMessageReceived == TRUE) && (ComIfRxMsgCfg_HMI[12].RxFlags.ReceptionStarted == FALSE))
#define ComIf_IsMessageReceptionHasError_HMI_diagnosticCommand() (ComIfRxMsgCfg_HMI[12].RxFlags.ErrorInReception)
#define ComIf_SetMessageProcessesed_HMI_diagnosticCommand()      ComIf_SetMessageProcessed(&(ComIfRxMsgCfg_HMI[12].RxFlags))



#define COMIF_DYNAMIC_DATA_LENGTH_ENABLED

/*************************************************/
/*               Type Definitions                */
/*************************************************/

typedef struct __ComIfTxFlags
{
    /* This structure must not exceed 8 bytes */
    
    /* Control Bits */
	UBYTE EnableAggregation      : 1; // If set, then the message will be aggregated instead of transmitting
	UBYTE ForceTransmit          : 1; // If set, then the aggregation enabled messages will be sent directly
	
	/* Status Bits */
	UBYTE PendingForTransmission : 1; // If set, then the message will be sent in next aggregation cycle
	UBYTE AggregatedInBuffer     : 1; // If set, then the message has been copied to the channel data buffer
	UBYTE PendingForConfirmation : 1; // If set, then the message will receive confirmation after the aggregation transmit cycle is completed
	
}ComIfTxFlags;

typedef struct __ComIfTxMessageConfig
{
	UBYTE ID;
	UBYTE Length;
#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
	UBYTE DynLength;
#endif
	UBYTE ChecksumLength;
	ComIfTxFlags TxFlags;
	UBYTE * ShadowBuffer;
	void (*TxConfCallback)(void);
	UBYTE (*TxCallback)(UBYTE *, UBYTE *);
}ComIfTxMessageConfig;

typedef struct __ComIfRxFlags
{
    /* This structure must not exceed 8 bytes */
    
	/* Status Bits */
	UBYTE ReceptionStarted   : 1; // If set, then the message has been started receiving
	UBYTE NewMessageReceived : 1; // If set, then the message has been received completely and waiting for the RxCbk to be called
	UBYTE ErrorInReception   : 1; // If set, then the message has been received, but there is an error in reception
	UBYTE RxRequest          : 1; // If set, then the message is requested by the application
	UBYTE RxRequestPlaced    : 1; // If set, then the message reception request has been placed to the underlying module
	
}ComIfRxFlags;

typedef struct __ComIfRxMessageConfig
{
	UBYTE ID;
	UBYTE Length;
	UBYTE ChecksumLength;
	ComIfRxFlags RxFlags;
	UBYTE CurRxngIdx;
	UBYTE * MessageBuffer;
	void (*RxCallback)(UBYTE, UBYTE*);
}ComIfRxMessageConfig;

typedef enum __ComIf_ChannelType
{
	C_ComIfChannel_HMI = 0,

	C_ComIfChannel_TOTAL = 1
}ComIf_ChannelType;

typedef UBYTE (*ComIf_ChannelTransmitType)(UWORD, void*);

typedef void (*ComIf_ErrorNotificationType)(ULONG, ULONG);

typedef UBYTE (*ComIf_ChannelRxRequestType)(UBYTE);

typedef struct __ComIfChannelFlags
{
	/* Reception related flag */
	UBYTE IsReceiving          : 1;
	UBYTE Delimit              : 1;
	UBYTE DLCVerified          : 1;
	UBYTE IsRxRequestEnabled   : 1;
	
	UBYTE IsTransmitting       : 1;
	UBYTE IsAggregationEnabled : 1;
	UBYTE HasAggregatedMsgs    : 1;
	
}ComIfChannelFlags;

#ifdef COMIF_TX_AGGREGATION_ENABLED
typedef struct __ComIf_TxAggCtrl_t
{
	UWORD TxCycle;
	UWORD TxCycleCounter;

	UWORD BufferLimit;
	UWORD CurrentBufferLength;
	
}ComIf_TxAggCtrl_t;
#endif

typedef struct __ComIf_ChannelConfigType
{
	ComIf_ChannelTransmitType Transmit;
	ComIf_ErrorNotificationType ErrorCallback;

#ifdef COMIF_RX_REQUEST_ENABLED
	ComIf_ChannelRxRequestType RequestReception;
	UWORD RxRequestTimeout;
	UWORD RxRequestTimeoutCounter;
#endif

	UBYTE * TxBuffer;
	UWORD TxBufferLength;
	
#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
	UBYTE DynamicMaxDataLength;
#endif
	UBYTE DataTxfrMethod;
	
	ComIfTxMessageConfig * TxMessages;
	UBYTE TotalTxMessages;
	
	ComIfRxMessageConfig * RxMessages;
	UBYTE TotalRxMessages;

	UBYTE RxMsgIndex;
	UBYTE RxMsgLength;
	ComIfChannelFlags ChannelFlags;

#ifdef COMIF_TX_AGGREGATION_ENABLED
	ComIf_TxAggCtrl_t * TxAggCtrl;
#endif
	
}ComIf_ChannelConfigType;

/*************************************************/
/*               Global Variables                */
/*************************************************/

extern ComIf_ChannelConfigType ComIf_ChannelConfig[];

/* Channel Buffers and Configuration */

/* For the Channel: HMI */
extern ComIfTxMessageConfig ComIfTxMsgCfg_HMI[];
extern UBYTE ComIfChannelTxBuffer_HMI[];
extern UBYTE ComIf_ShadowBuffer_HMI_machineStatus[];
extern UBYTE ComIf_ShadowBuffer_HMI_sensorData[];
extern UBYTE ComIf_ShadowBuffer_HMI_waterConsumptionStatus[];
extern UBYTE ComIf_ShadowBuffer_HMI_ErrorData[];
extern UBYTE ComIf_ShadowBuffer_HMI_diagnosticData[];
extern ComIfRxMessageConfig ComIfRxMsgCfg_HMI[];
extern UBYTE ComIf_RxMessageBuffer_HMI_androidData[];
extern UBYTE ComIf_RxMessageBuffer_HMI_recipeStepConfiguration[];
extern UBYTE ComIf_RxMessageBuffer_HMI_recipeStep1[];
extern UBYTE ComIf_RxMessageBuffer_HMI_recipeStep2[];
extern UBYTE ComIf_RxMessageBuffer_HMI_recipeStep3[];
extern UBYTE ComIf_RxMessageBuffer_HMI_recipeStep4[];
extern UBYTE ComIf_RxMessageBuffer_HMI_recipeStep5[];
extern UBYTE ComIf_RxMessageBuffer_HMI_recipeStep6[];
extern UBYTE ComIf_RxMessageBuffer_HMI_combiRecipeSettings[];
extern UBYTE ComIf_RxMessageBuffer_HMI_steamRecipeSettings[];
extern UBYTE ComIf_RxMessageBuffer_HMI_bakingRecipeSettings[];
extern UBYTE ComIf_RxMessageBuffer_HMI_washSettings[];
extern UBYTE ComIf_RxMessageBuffer_HMI_diagnosticCommand[];

/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

static inline void ComIf_SetMessageProcessed(ComIfRxFlags * RxFlags)
{
	if(RxFlags != NULL)
	{
		RxFlags->NewMessageReceived = FALSE;
#ifdef COMIF_RX_REQUEST_ENABLED
		RxFlags->RxRequest = FALSE;
		RxFlags->RxRequestPlaced = FALSE;
#endif
	}
}

/*************************************************/
/*          Extern Function Declarations         */
/*************************************************/

extern UBYTE ComIf_Rx_Request(ComIf_ChannelType ChannelIndex, UBYTE MsgIndex);
extern UBYTE ComIf_Rx_CancelRequest(ComIf_ChannelType ChannelIndex, UBYTE MsgIndex);

/* Channel Specific Rx Indication Functions */
extern UBYTE ComIf_RxIndication_HMI(UBYTE DataByte);

#endif /* __COMIF_CONFIG_H__ */

