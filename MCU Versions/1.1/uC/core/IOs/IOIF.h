#ifndef _IOIF_H
#define _IOIF_H
/**********************************************************/
/*          Input Output Interface	                      */
/**********************************************************/

/**********************************************************/
/* Header Inclusions                                      */
/**********************************************************/
#include "Includes.h"
#include PORTSINIT_H
/**********************************************************/
/* Macro Definitions                                      */
/**********************************************************/

/****Machine Status Control Macros****/
#define Send_MachineStatus()						machineStatusMain()						
/****LIGHT Control Macros****/

#define TURN_ON_LIGHT()									GPIO_WritePin(GPIOD,GPIO_PIN_5, GPIO_PIN_SET)
#define TURN_OFF_LIGHT()								GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET)

#define TURN_ON_CHARGING()							GPIO_WritePin(GPIOC,GPIO_PIN_0, GPIO_PIN_SET)
#define TURN_OFF_CHARGING()							GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET)

/****Wash Control Macros****/

#define TURN_ON_WASH_PUMP()							GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_SET)
#define TURN_OFF_WASH_PUMP()						GPIO_WritePin(GPIOD,GPIO_PIN_2, GPIO_PIN_RESET)	

/****Door status control Macros****/

#define IS_DOOR_CLOSED()							  	GPIO_ReadPin(GPIOB,GPIO_PIN_7)

#define IsDoorClosed()									(doorStatus == E_doorClosed)
#define IsDoorOpen()										(doorStatus == E_doorOpen)

/****Fan Motor Macros****/

#define IS_FAN_MOTOR_RUNNING()					GPIO_ReadPin(GPIOB,GPIO_PIN_6)

#define IsFanMotorRunning()							fanMotorRunningStatus == TRUE
						
#define TURN_FORWARD_MOTOR_ON()					GPIO_WritePin(GPIOD, GPIO_PIN_4,GPIO_PIN_SET)
#define TURN_FORWARD_MOTOR_OFF()				GPIO_WritePin(GPIOD, GPIO_PIN_4,GPIO_PIN_RESET)

#define IsForwardMotorRunning()					GPIO_ReadPin(GPIOD, GPIO_PIN_4)
#define IsReverseMotorRunning()					GPIO_ReadPin(GPIOD, GPIO_PIN_3)

#define TURN_REVERSE_MOTOR_ON()					GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_SET)
#define TURN_REVERSE_MOTOR_OFF()				GPIO_WritePin(GPIOD, GPIO_PIN_3,GPIO_PIN_RESET)

#define TurnonMotorFor()								fanMotorControl = E_fanMotorRunForward
#define TurnOnMotorRev()								fanMotorControl = E_fanMotorRunReverse
#define TurnOffMotor()									fanMotorControl = E_fanMotor_OFF

/****Steam Control Macros****/

#define TURN_ON_WATER_INLET_VALVE()			{IsWaterInletOpenFlag = TRUE; \
																					GPIO_WritePin(GPIOD,GPIO_PIN_1, GPIO_PIN_SET);}
																					
#define TURN_OFF_WATER_INLET_VALVE()		{IsWaterInletOpenFlag = FALSE; \
																					GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_RESET);}

#define TOGGLE_WATER_INLET_VALVE()			GPIO_TogglePin(GPIOD,GPIO_PIN_1);

#define TurnOnSteam()										steamControl 	= E_steamStepOnOff
#define TurnOffSteam()									steamControl	= E_steamDeactivate
#define	SteamOn()												steamControl 	= E_steamOn
/****Heater Control Macros****/

#define TurnOnHeater()									heaterControl = E_heater_ON
#define TurnOffHeater()									heaterControl = E_heater_OFF

#define IsHeaterTurnedOn()							heaterControl == E_heater_ON
#define IsHeaterTurnedOff()							heaterControl == E_heater_OFF

#define TURN_ON_HEATER()								GPIO_WritePin(GPIOD,GPIO_PIN_0, GPIO_PIN_SET)
#define TURN_OFF_HEATER()								GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET)

/****Drain Valve Control Macros****/

#define DRAIN_VALVE_OPEN()							GPIO_WritePin(GPIOD,GPIO_PIN_6, GPIO_PIN_SET)
#define DRAIN_VALVE_CLOSE()							GPIO_WritePin(GPIOD,GPIO_PIN_6, GPIO_PIN_RESET) 

#define IS_DRAIN_VALVE_OPEN()						GPIO_ReadPin(GPIOB,GPIO_PIN_4)
#define IS_DRAIN_VALVE_CLOSED()					GPIO_ReadPin(GPIOB,GPIO_PIN_5)

#define IsDrainValveOpen()							drainValveStatus == S_drainValveOpen
#define IsDrainValveClosed()						drainValveStatus == S_drainValveClosed

#define OpenDrainValve()								drainValveControlState = E_openDrainValve
#define CloseDrainValve()								drainValveControlState = E_closeDrainValve

#define OpenDValve()										drainValveControlState = E_continouslyOpen

#define DeactivateDrainValveCtrl()			drainValveControlState = E_DeactivateDrainValveControl

/****BLE Control Macros****/
#define IsBluetoothConnected() 					GPIO_ReadPin(GPIOB,GPIO_PIN_12)

/**********************************************************/
/* Type Definitions                                       */
/**********************************************************/
typedef enum 
{
	E_waterInlet_OFF=0,
	E_waterInlet_ON
	
}waterInletValveType;

typedef enum 
{
	E_heaterIdle = 0,
	E_heaterTurnOnWaitTime,
	E_heater_OFF,
	E_heater_ON
	
}heaterControlType;


typedef enum 
{
	E_fanMotorIdle = 0,
	E_fanMotorRunForward,
	E_fanMotorRunReverse,
	E_fanMotorDirectionTimout,
	E_fanMotor_OFF
}fanMotorControlType;

typedef enum 
{
	E_NotDetected = 0,
	E_doorOpen,
	E_doorClosed
	
}doorStaus_EN;


typedef enum
{
	E_steamIdle = 0,
	E_steamOff,
	E_steamStepOnOff,
	E_steamOn,
	E_steamTimeOut,
	E_steamDeactivate
	
}steamControlType;


typedef enum
{
	S_drainValveStatusNotConfigured = 0,
	S_drainValveOpen,
	S_drainValveClosed
	
}drainValveStatusType;


typedef enum
{
	E_DrainValveIdle = 0,
	E_continouslyOpen,
	E_openDrainValve,
	E_closeDrainValve,
	E_DrainValveOnTime,
	E_DrainValveOffTime,
	E_DeactivateDrainValveControl
	
}drainValveControlType;


typedef enum
{
	MS_machineIdle = 0,
	MS_preparingToCook,
	MS_cooking,
	MS_cookingPaused,
	MS_preparingToWash,
	MS_Washing,
	MS_washingPaused
	
}machineStaus_EN;

typedef union _MachineStatus
{
	struct
	{
		/***Byte 0***/
		UBYTE DOI : 1;
		machineStaus_EN MachineStaus : 3;
		UBYTE DOR : 1;
		UBYTE DCR : 1;
		UBYTE NWF : 1;
		UBYTE BOOT : 1;
	};
	
	UBYTE Byte;
	
}machineStatus_ST;
/**********************************************************/
/* Global Variable Declarations                           */
/**********************************************************/


/**********************************************************/
/* Function Declaration                                   */
/**********************************************************/
extern void heaterControlMain();
extern UBYTE updateDrainValveSetting(ULONG onTimeout,ULONG OffTimout);
extern UBYTE updateMotorSpeed(UBYTE setThresholdLevel,UBYTE InputDACdata);
extern void machineStatusMain();

extern doorStaus_EN doorStatus;

extern fanMotorControlType fanMotorControl ;
extern fanMotorControlType prevMotorControlState;
extern BOOL fanMotorRunningStatus;

extern heaterControlType heaterControl;

extern ULONG steamLevelOnTime ;
extern ULONG steamLevelOffTime ;
extern ULONG SteamLevelTimout;
extern steamControlType steamControl;
extern BOOL IsWaterInletOpenFlag; 

extern drainValveControlType drainValveControlState;
extern drainValveStatusType drainValveStatus;

extern machineStatus_ST machineStatus;

extern BOOL ovenPauseControl;
extern BOOL OpenRequest;

/**********************************************************/
/* Inline Function Definitions                            */
/**********************************************************/

inline void TurnOnMotor()
{
	if(fanMotorControl == E_fanMotorIdle)
	{
		fanMotorControl = E_fanMotorRunForward;
	}
	else
	{
		if(prevMotorControlState == E_fanMotorRunForward)
		{
			fanMotorControl = E_fanMotorRunForward;
		}
		else if(prevMotorControlState == E_fanMotorRunReverse)
		{
			fanMotorControl = E_fanMotorRunReverse;
		}
	}
}	 

#endif