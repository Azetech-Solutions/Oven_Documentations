
#ifndef __DIAG_ID_H__
#define __DIAG_ID_H__

/*************************************************/
/* IDs For DiagEvent_CookingConfig_Error         */
/*************************************************/
#define Invalid_MaxTemprature			1u
#define Invalid_CookingMode				2u

#define Invalid_numberOfSteps 		3u
#define Invalid_StepIndex					4u

#define RecipeStepConfigError			5u
#define CombiRecipeConfigError		6u
#define SteamRecipeConfigError		7u
#define BakingRecipeConfigError		8u
#define RecipeStep1ConfigError		9u
#define RecipeStep2ConfigError		10u
#define RecipeStep3ConfigError		11u
#define RecipeStep4ConfigError		12u
#define RecipeStep5ConfigError		13u
#define RecipeStep6ConfigError		14u
#define RecipeStep7ConfigError		15u

#define RecipeConfigFlagCheck			16u
/*************************************************/
/* IDs For DiagEvent_Wash_Error         				 */
/*************************************************/
#define Invalid_WashTemprature			0u
#define Invalid_CD_Temprature				1u
#define Invalid_DrainvalveTimeout		2u
#define Invalid_FanSpeed						3u
#define Invalid_SteamLevelOnTime		4u
#define Invalid_WashTimeOut					5u	
#define WashTempratureNotAttained		6u
/*************************************************/
/* IDs For DiagEvent_Heater_Error         			 */
/*************************************************/

/*************************************************/
/* IDs For DiagEvent_DrainValve_Error         	 */
/*************************************************/

/*************************************************/
/* IDs For DiagEvent_Motor_Error         				 */
/*************************************************/
#define MOTOR_NOT_RUNNING				0u
#define MOTOR_NOT_TURNING_OFF		1u
/*************************************************/
/* IDs For DiagEvent_Steam_Error         				 */
/*************************************************/
#define STEAM_NOT_WORKING 		0u
#define STEAM_NOT_TURNING_OFF 1u

/*************************************************/
/* IDs For DiagEvent_HMI_ComIf_Error         		 */
/*************************************************/


#endif
