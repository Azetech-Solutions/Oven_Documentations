
/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "stm32g0xx.h"                  // Device header
#include "Includes.h"
#include SPI_H
#include COMIF_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/
#define TEMP1_CS_LOW()      				GPIO_WritePin(GPIOB,GPIO_PIN_2,0)
#define TEMP1_CS_HIGH()    					GPIO_WritePin(GPIOB,GPIO_PIN_2,1)

#define TEMP2_CS_LOW()      				GPIO_WritePin(GPIOB,GPIO_PIN_1,0)
#define TEMP2_CS_HIGH()     				GPIO_WritePin(GPIOB,GPIO_PIN_1,1)

#define MCP3008_CS_LOW      				GPIO_WritePin(GPIOB,GPIO_PIN_0,0);
#define MCP3008_CS_HIGH     				GPIO_WritePin(GPIOB,GPIO_PIN_0,1);

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/

typedef enum
{
	C_CurrentPhase_1 = 0,
	C_CurrentPhase_2,
	C_CurrentPhase_3,
	C_VoltagePhase_1,
	C_VoltagePhase_2,
	C_VoltagePhase_3,
	
	C_DacFeedBackChannel,
	
	C_TotalAdcChannels
	
}AdcChannels_En;

typedef enum
{
	C_TempratureSensor_1 = 0,
	C_TempratureSensor_2,
	
	C_TotalTempSensorChannels
	
}TempSensorChannel_En;


typedef union
{
	struct
	{
		/* Bytes 0 - 6 */
		UBYTE PM_Data[6]; // Power Measurement Datas
		/* Bytes - 7 */
		UBYTE OvenTempS1MSB : 8;
		/* Bytes - 8 */
		UBYTE Reserved_1		: 2;
		UBYTE OvenTempS1LSB : 6;
	};
	
	UBYTE Bytes[8];
	
}SensorData_ST;//Sensor Data Structure

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
extern void sensorDataMain();