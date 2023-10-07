/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/

#include "spiSensors.h"
#include DEBUG_H

/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/
extern void spiTransmitReceiveIntr(UBYTE TxData);

SensorData_ST sensorData;

volatile UWORD ovenTemprature = 0;

ULONG Count = 0;

UBYTE IntrCount = 0;
UBYTE FByte = 0;
UBYTE ChannelIndex = 0;
UBYTE SampleCounter = 0;

UBYTE ResultData[6] = {0};

/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/

/* Call this Function to Read the Temprature From the MAX6675 */

float readTemprature(BOOL Channel)
{
	BOOL TCF=0;                                          	// Thermocouple Connection acknowledge Flag

	UBYTE Data[2];                                    	// Raw Data from MAX6675
	
	float Temp=0; 																				// Temperature Variable
														 
	(Channel==0)? TEMP1_CS_LOW() : TEMP2_CS_LOW() ;     	// Low State for SPI Communication

	Data[0] = spiTransmitReceive(0x00); 								// Send Empty byte to Receive the first MSB byte

	Data[1] = spiTransmitReceive(0x00);  								// Send Empty byte to Receive the first LSB byte
	
	(Channel==0)? TEMP1_CS_HIGH() : TEMP2_CS_HIGH() ;			// High State for SPI Communication

	TCF  = (((Data[0])>>2)& 0x0001);        						// State of Connecting

	Temp = ((((Data[1]|Data[0]<<8)))>>3);             // Temperature Data Extraction

	// Waits for Chip Ready(according to Datasheet, the max time for conversion is 220ms)

	return Temp;
}


/* Call this function to read the adc values from MCP3008 
 * Send the channel Values in between 0 to 7
 * If this function returns negative value it means wrong channel selection.
*/

UWORD readMCP3008(UBYTE Channel)
{
	if ((Channel < 0) || (Channel > 7))
	{
		  return -1;
	}

	UWORD result = 0 ,FirstByte = 0 ;

	UBYTE ConfigBits = 0x80;													// single-ended Conversion

	ConfigBits |= (Channel << 4); 										// Channel selection 

	MCP3008_CS_LOW; 																	// chip Select Low

	(void)spiTransmitReceive(0x01); 									// Start Bit

	FirstByte =  spiTransmitReceive(ConfigBits); 			// send the Config bits and receive the first byte

	FirstByte = (UWORD)((FirstByte & 0x03)<< 8); 			// use only first 2 bits

	result =  spiTransmitReceive(0x00); 							// Send empty byte and receive second byte

	result |= FirstByte; 															// combine the 2 bytes 

	MCP3008_CS_HIGH; 																	// Make chip select high

	return result;
}


/* TODO : Now just Raw data Is Send to the Comif Buffer Have Calcuate the 
	 Actual ADC Data after the Power Measurement Circuit Design*/


UWORD readVoltage[3] = {0};
UWORD readCurrent[3] = {0};

UWORD Voltage[3] = {0};
UWORD Current[3] = {0};

/*readVC fucntion is used for Reading the Voltage and Current values from 3 phases*/

void readVC()
{
	/* Read ADC Datas From MCP3008 IC */
	
	UBYTE cIndex = 0,Vindex = 0 ;
	
	for(UBYTE i = 7 ;i >= 5;i--)
	{
		readVoltage[Vindex] = readMCP3008(i);
		Vindex++;
	}
	
	for(UBYTE i = 4 ;i >= 2;i--)
	{
		readCurrent[cIndex] = readMCP3008(i);
		cIndex++;
	}

	for(UBYTE i = 0 ;i < 3;i++)
	{
		if(readVoltage[i] > Voltage[i])
		{
			Voltage[i] = readVoltage[i];
		}
	}
	
	for(UBYTE i = 0 ;i < 3;i++)
	{
		if(readCurrent[i] > Current[i])
		{
			Current[i] = readCurrent[i];
		}
	}
}


void sensorDataMain()
{
	Count++;
	
	SensorData_ST *SensorData = &sensorData;

	if(Count == 10)
	{	
		for(int i = 0;i < 3;i++)
		{
			Voltage[i] = 0;
			readVoltage[i]=0;
			Current[i]=0;
		}
		
		Count = 0;
	}
		
	for(UBYTE i=0;i<3;i++)
	{
		SensorData->PM_Data[i] = ((Current[i]*0.08)*4);
	}
	
	UBYTE j = 0;
	
	for(UBYTE i=3;i<6;i++)
	{
		UWORD Volt = (Voltage[j]*1.15);
		
		if(Volt > 20)
		{
			SensorData->PM_Data[i] = Volt; 
		}
		else
		{
			SensorData->PM_Data[i] = 0;
		}
		
		j++;
	}
	
	
	UWORD TempS1 = readTemprature(C_TempratureSensor_1);			//Read the Temprature sensor 1 Value
	
//	UWORD TempS2 = readTemprature(C_TempratureSensor_2);			//Read the Temprature sensor 2 Value

	ovenTemprature = (UW)(TempS1*0.25);//This Calculation will convert the bits into degree celcius 
	
	sensorData.OvenTempS1MSB = ((ovenTemprature & 0x3FC0) >> 6);
	sensorData.OvenTempS1LSB = (ovenTemprature & 0x003F) ;
	
	/* Store the Sensor data to Comif Buffer */
	
	UBYTE *Data = ComIf_GetShadowBuffer_HMI_sensorData();
	
	for(UBYTE i=0; i < ComIf_GetLength_HMI_sensorData() ; i++)
	{
			Data[i] = sensorData.Bytes[i];
	}
	
	ComIf_TransmitFromBuffer_HMI_sensorData();
}