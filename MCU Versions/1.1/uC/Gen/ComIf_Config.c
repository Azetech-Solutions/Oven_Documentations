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

#include "ComIf.h"

/******************************************************/
/*           Global Variable Definitions              */
/******************************************************/

/* Channel Declarations */

/* -------------------------------------------------- */
/* For HMI Channel */
/* -------------------------------------------------- */

extern UBYTE HMI_Transmit(UWORD Length, void * Data);
extern void HMI_ComIf_ErrorNotification(ULONG Debug0, ULONG Debug1);

UBYTE ComIfChannelTxBuffer_HMI[256];

UBYTE ComIf_ShadowBuffer_HMI_machineStatus[1];
extern void HMI_TxConfCbk(void);
UBYTE ComIf_ShadowBuffer_HMI_sensorData[8];
UBYTE ComIf_ShadowBuffer_HMI_waterConsumptionStatus[3];
UBYTE ComIf_ShadowBuffer_HMI_ErrorData[9];
UBYTE ComIf_ShadowBuffer_HMI_diagnosticData[1];

ComIfTxMessageConfig ComIfTxMsgCfg_HMI[5] = {
	{
		/* machineStatus */
		/* ID */        0x35,
		/* Length */    1,
	#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* DynLength */ 0,
	#endif
		/* CHKLEN */    1,
		/* Tx Flags */  {
							0, // EnableAggregation
							0, // Force Transmit
							0, // PendingForTransmission
							0, // AggregatedInBuffer
							0  // PendingForConfirmation
						},
		/* Buffer */    ComIf_ShadowBuffer_HMI_machineStatus,
		/* TxConfCbk */ &HMI_TxConfCbk,
		/* TxCbk */     NULL
	},
	{
		/* sensorData */
		/* ID */        0x5D,
		/* Length */    8,
	#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* DynLength */ 0,
	#endif
		/* CHKLEN */    1,
		/* Tx Flags */  {
							0, // EnableAggregation
							0, // Force Transmit
							0, // PendingForTransmission
							0, // AggregatedInBuffer
							0  // PendingForConfirmation
						},
		/* Buffer */    ComIf_ShadowBuffer_HMI_sensorData,
		/* TxConfCbk */ NULL,
		/* TxCbk */     NULL
	},
	{
		/* waterConsumptionStatus */
		/* ID */        0x3C,
		/* Length */    3,
	#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* DynLength */ 0,
	#endif
		/* CHKLEN */    1,
		/* Tx Flags */  {
							0, // EnableAggregation
							0, // Force Transmit
							0, // PendingForTransmission
							0, // AggregatedInBuffer
							0  // PendingForConfirmation
						},
		/* Buffer */    ComIf_ShadowBuffer_HMI_waterConsumptionStatus,
		/* TxConfCbk */ NULL,
		/* TxCbk */     NULL
	},
	{
		/* ErrorData */
		/* ID */        0xED,
		/* Length */    9,
	#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* DynLength */ 0,
	#endif
		/* CHKLEN */    1,
		/* Tx Flags */  {
							0, // EnableAggregation
							0, // Force Transmit
							0, // PendingForTransmission
							0, // AggregatedInBuffer
							0  // PendingForConfirmation
						},
		/* Buffer */    ComIf_ShadowBuffer_HMI_ErrorData,
		/* TxConfCbk */ NULL,
		/* TxCbk */     NULL
	},
	{
		/* diagnosticData */
		/* ID */        0xDD,
		/* Length */    1,
	#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* DynLength */ 0,
	#endif
		/* CHKLEN */    1,
		/* Tx Flags */  {
							0, // EnableAggregation
							0, // Force Transmit
							0, // PendingForTransmission
							0, // AggregatedInBuffer
							0  // PendingForConfirmation
						},
		/* Buffer */    ComIf_ShadowBuffer_HMI_diagnosticData,
		/* TxConfCbk */ NULL,
		/* TxCbk */     NULL
	},
};

extern void androidDataRxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_androidData[3];
extern void recipeStepConfigRxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_recipeStepConfiguration[2];
extern void recipeStep1RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_recipeStep1[5];
extern void recipeStep2RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_recipeStep2[5];
extern void recipeStep3RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_recipeStep3[5];
extern void recipeStep4RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_recipeStep4[5];
extern void recipeStep5RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_recipeStep5[5];
extern void recipeStep6RxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_recipeStep6[5];
extern void combiRecipeRxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_combiRecipeSettings[10];
extern void steamRecipeSettingsRxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_steamRecipeSettings[10];
extern void bakingRecipeSettingsRxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_bakingRecipeSettings[5];
extern void washSettingsRxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_washSettings[7];
extern void diagnosticCommandRxCbk(UBYTE Length, UBYTE *Data);
UBYTE ComIf_RxMessageBuffer_HMI_diagnosticCommand[2];

ComIfRxMessageConfig ComIfRxMsgCfg_HMI[13] = {
	{
		/* androidData */
		/* ID */      0xAD,
		/* Length */  2,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_androidData,
		/* RxCbk */   &androidDataRxCbk
	},
	{
		/* recipeStepConfiguration */
		/* ID */      0x5C,
		/* Length */  1,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_recipeStepConfiguration,
		/* RxCbk */   &recipeStepConfigRxCbk
	},
	{
		/* recipeStep1 */
		/* ID */      0x51,
		/* Length */  4,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_recipeStep1,
		/* RxCbk */   &recipeStep1RxCbk
	},
	{
		/* recipeStep2 */
		/* ID */      0x52,
		/* Length */  4,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_recipeStep2,
		/* RxCbk */   &recipeStep2RxCbk
	},
	{
		/* recipeStep3 */
		/* ID */      0x53,
		/* Length */  4,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_recipeStep3,
		/* RxCbk */   &recipeStep3RxCbk
	},
	{
		/* recipeStep4 */
		/* ID */      0x54,
		/* Length */  4,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_recipeStep4,
		/* RxCbk */   &recipeStep4RxCbk
	},
	{
		/* recipeStep5 */
		/* ID */      0x55,
		/* Length */  4,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_recipeStep5,
		/* RxCbk */   &recipeStep5RxCbk
	},
	{
		/* recipeStep6 */
		/* ID */      0x56,
		/* Length */  4,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_recipeStep6,
		/* RxCbk */   &recipeStep6RxCbk
	},
	{
		/* combiRecipeSettings */
		/* ID */      0xC5,
		/* Length */  9,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_combiRecipeSettings,
		/* RxCbk */   &combiRecipeRxCbk
	},
	{
		/* steamRecipeSettings */
		/* ID */      0x65,
		/* Length */  9,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_steamRecipeSettings,
		/* RxCbk */   &steamRecipeSettingsRxCbk
	},
	{
		/* bakingRecipeSettings */
		/* ID */      0xB5,
		/* Length */  4,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_bakingRecipeSettings,
		/* RxCbk */   &bakingRecipeSettingsRxCbk
	},
	{
		/* washSettings */
		/* ID */      0x33,
		/* Length */  6,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_washSettings,
		/* RxCbk */   &washSettingsRxCbk
	},
	{
		/* diagnosticCommand */
		/* ID */      0xDC,
		/* Length */  1,
		/* CHKLEN */  1,
		/* RxFlags */ {
						0, // ReceptionStarted
						0, // NewMessageReceived
						0, // ErrorInReception
						0, // RxRequest
						0  // RxRequestPlaced
					  },
		/* RxngIdx */ 0,
		/* Buffer */  ComIf_RxMessageBuffer_HMI_diagnosticCommand,
		/* RxCbk */   &diagnosticCommandRxCbk
	},
};


ComIf_ChannelConfigType ComIf_ChannelConfig[C_ComIfChannel_TOTAL] = 
{
    {	                                    /* For HMI ComIf Channel */
    	/* Transmit Function */             &HMI_Transmit,
    	/* Error Notification Function */   &HMI_ComIf_ErrorNotification,
#ifdef COMIF_RX_REQUEST_ENABLED
		/* Rx Request Function */           NULL,
		/* Rx Timeout Time */               0,
		/* Rx Timeout Time Counter */       0,
#endif
    	/* Transmit Buffer */               ComIfChannelTxBuffer_HMI,
    	/* Transmit Buffer Length */        256,
#ifdef COMIF_DYNAMIC_DATA_LENGTH_ENABLED
		/* Dynamic Max Data Length */       64,
#endif
    	/* Data Transfer Method */          COMIF_DATA_TXFR_METHOD_BYTES,
		/* Tx Message Config Pointer */     ComIfTxMsgCfg_HMI,
		/* Total Number of Tx Messages */   5,
		/* Rx Message Config Pointer */     ComIfRxMsgCfg_HMI,
		/* Total Number of Rx Messages */   13,
		/* Index of Receiving Message */    P_COMIF_INVALID_HANDLE,
		/* Length of Receiving Message */   0,
		/* Channel Specific Flags */
		{
			0,  // IsReceiving
			0,  // Delimit
			0,  // DLCVerified
			0,  // IsRxRequestEnabled
			0,  // IsTransmitting
			0,  // IsAggregationEnabled
			0,  // HasAggregatedMsgs
		},

#ifdef COMIF_TX_AGGREGATION_ENABLED
	#ifdef TX_AGGREGATION_ENABLED_HMI
        /* Tx Aggregation Control */        &(ComIf_TxAggCtrl_HMI)
	#else
        /* Tx Aggregation Control */        NULL
	#endif
#endif
    },
};

/***************************************************/
/* Function Definitions                            */
/***************************************************/
/* Channel Specific Rx Indication Functions */

UBYTE ComIf_RxIndication_HMI(UBYTE DataByte)
{
	return ComIf_RxIndication(((UBYTE)C_ComIfChannel_HMI), DataByte);
}

