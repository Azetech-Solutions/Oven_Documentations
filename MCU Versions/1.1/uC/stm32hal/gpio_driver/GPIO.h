
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G0GPIO_H
#define STM32G0GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#define assert_param(expr) ((void)0U)
	
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0uL :\
                                      ((__GPIOx__) == (GPIOB))? 1uL :\
                                      ((__GPIOx__) == (GPIOC))? 2uL :\
                                      ((__GPIOx__) == (GPIOD))? 3uL : 5uL)
/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stm32g0xx.h"
#include "stm32g071xx.h"

/**
  * @brief   GPIO Init structure definition
  */

#define PORTA_CLOCK_ENABLE()   	RCC->IOPENR |= (1<<0)
#define PORTB_CLOCK_ENABLE()   	RCC->IOPENR |= (1<<1)
#define PORTC_CLOCK_ENABLE()   	RCC->IOPENR |= (1<<2)
#define PORTD_CLOCK_ENABLE()   	RCC->IOPENR |= (1<<3)

#define IsClockEnabled_PortA() (RCC->IOPENR & (1<<0))
#define IsClockEnabled_PortB() (RCC->IOPENR & (1<<1))
#define IsClockEnabled_PortC() (RCC->IOPENR & (1<<2))
#define IsClockEnabled_PortD() (RCC->IOPENR & (1<<3))

/*	Macros to enable Clock	*/
#define RCC_USART1_CLK_ENABLE()	(RCC->APBENR2 |= (1<<14))
#define RCC_USART2_CLK_ENABLE()	(RCC->APBENR1 |= (1<<17))

/*------------------------- STM32G081xx / STM32G071xx ------------------------*/
/**
  * @brief   AF 0 selection
  */
#define GPIO_AF0_CEC           ((uint8_t)0x00)  /*!< CEC Alternate Function mapping */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00)  /*!< EVENTOUT Alternate Function mapping */
#define GPIO_AF0_IR            ((uint8_t)0x00)  /*!< IR Alternate Function mapping */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00)  /*!< LPTIM1 Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00)  /*!< MCO (MCO1) Alternate Function mapping */
#define GPIO_AF0_OSC           ((uint8_t)0x00)  /*!< OSC (By pass and Enable) Alternate Function mapping */
#define GPIO_AF0_OSC32         ((uint8_t)0x00)  /*!< OSC32 (By pass and Enable) Alternate Function mapping */
#define GPIO_AF0_SWJ           ((uint8_t)0x00)  /*!< SWJ (SWD) Alternate Function mapping */
#define GPIO_AF0_SPI1          ((uint8_t)0x00)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF0_SPI2          ((uint8_t)0x00)  /*!< SPI2 Alternate Function mapping */
#define GPIO_AF0_TIM14         ((uint8_t)0x00)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF0_USART1        ((uint8_t)0x00)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF0_USART2        ((uint8_t)0x00)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF0_USART3        ((uint8_t)0x00)  /*!< USART3 Alternate Function mapping */
#define GPIO_AF0_UCPD1         ((uint8_t)0x00)  /*!< UCPD1 Alternate Function mapping */
#define GPIO_AF0_UCPD2         ((uint8_t)0x00)  /*!< UCPD2 Alternate Function mapping */

/**
  * @brief   AF 1 selection
  */
#define GPIO_AF1_CEC           ((uint8_t)0x01)  /*!< CEC Alternate Function mapping */
#define GPIO_AF1_IR            ((uint8_t)0x01)  /*!< IR Alternate Function mapping */
#define GPIO_AF1_LPUART1       ((uint8_t)0x01)  /*!< LPUART1 Alternate Function mapping */
#define GPIO_AF1_OSC           ((uint8_t)0x01)  /*!< OSC (By pass and Enable) Alternate Function mapping */
#define GPIO_AF1_SPI1          ((uint8_t)0x01)  /*!< SPI2 Alternate Function mapping */
#define GPIO_AF1_SPI2          ((uint8_t)0x01)  /*!< SPI2 Alternate Function mapping */
#define GPIO_AF1_TIM1          ((uint8_t)0x01)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF1_TIM3          ((uint8_t)0x01)  /*!< TIM3 Alternate Function mapping */
#define GPIO_AF1_USART1        ((uint8_t)0x01)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF1_USART2        ((uint8_t)0x01)  /*!< USART2 Alternate Function mapping */
#define GPIO_AF1_USART4        ((uint8_t)0x01)  /*!< USART4 Alternate Function mapping */
#define GPIO_AF1_UCPD1         ((uint8_t)0x01)  /*!< UCPD1 Alternate Function mapping */
#define GPIO_AF1_UCPD2         ((uint8_t)0x01)  /*!< UCPD2 Alternate Function mapping */

/**
  * @brief   AF 2 selection
  */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02)  /*!< LPTIM1 Alternate Function mapping */
#define GPIO_AF2_LPTIM2        ((uint8_t)0x02)  /*!< LPTIM2 Alternate Function mapping */
#define GPIO_AF2_TIM1          ((uint8_t)0x02)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF2_TIM2          ((uint8_t)0x02)  /*!< TIM2 Alternate Function mapping */
#define GPIO_AF2_TIM14         ((uint8_t)0x02)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF2_TIM15         ((uint8_t)0x02)  /*!< TIM15 Alternate Function mapping */
#define GPIO_AF2_TIM16         ((uint8_t)0x02)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF2_TIM17         ((uint8_t)0x02)  /*!< TIM17 Alternate Function mapping */

/**
  * @brief   AF 3 selection
  */
#define GPIO_AF3_UCPD1         ((uint8_t)0x03)  /*!< UCPD1 Alternate Function mapping */
#define GPIO_AF3_UCPD2         ((uint8_t)0x03)  /*!< UCPD2 Alternate Function mapping */

/**
  * @brief   AF 4 selection
  */
#define GPIO_AF4_SPI2          ((uint8_t)0x04)  /*!< SPI2 Alternate Function mapping */
#define GPIO_AF4_TIM14         ((uint8_t)0x04)  /*!< TIM14 Alternate Function mapping */
#define GPIO_AF4_TIM15         ((uint8_t)0x04)  /*!< TIM15 Alternate Function mapping */
#define GPIO_AF4_USART1        ((uint8_t)0x04)  /*!< USART1 Alternate Function mapping */
#define GPIO_AF4_USART3        ((uint8_t)0x04)  /*!< USART3 Alternate Function mapping */
#define GPIO_AF4_USART4        ((uint8_t)0x04)  /*!< USART4 Alternate Function mapping */
#define GPIO_AF4_UCPD1         ((uint8_t)0x04)  /*!< UCPD1 Alternate Function mapping */
#define GPIO_AF4_UCPD2         ((uint8_t)0x04)  /*!< UCPD2 Alternate Function mapping */

/**
  * @brief   AF 5 selection
  */
#define GPIO_AF5_LPTIM1        ((uint8_t)0x05)  /*!< LPTIM1 Alternate Function mapping */
#define GPIO_AF5_LPTIM2        ((uint8_t)0x05)  /*!< LPTIM2 Alternate Function mapping */
#define GPIO_AF5_SPI1          ((uint8_t)0x05)  /*!< SPI1 Alternate Function mapping */
#define GPIO_AF5_SPI2          ((uint8_t)0x05)  /*!< SPI2 Alternate Function mapping */
#define GPIO_AF5_TIM1          ((uint8_t)0x05)  /*!< TIM1 Alternate Function mapping */
#define GPIO_AF5_TIM15         ((uint8_t)0x05)  /*!< TIM15 Alternate Function mapping */
#define GPIO_AF5_TIM16         ((uint8_t)0x05)  /*!< TIM16 Alternate Function mapping */
#define GPIO_AF5_TIM17         ((uint8_t)0x05)  /*!< TIM17 Alternate Function mapping */
#define GPIO_AF5_USART3        ((uint8_t)0x05)  /*!< USART3 Alternate Function mapping */

/**
  * @brief   AF 6 selection
  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06)  /*!< I2C1 Alternate Function mapping */
#define GPIO_AF6_I2C2          ((uint8_t)0x06)  /*!< I2C2 Alternate Function mapping */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06)  /*!< LPUART1 Alternate Function mapping */
#define GPIO_AF6_UCPD1         ((uint8_t)0x06)  /*!< UCPD1 Alternate Function mapping */
#define GPIO_AF6_UCPD2         ((uint8_t)0x06)  /*!< UCPD2 Alternate Function mapping */

/**
  * @brief   AF 7 selection
  */
#define GPIO_AF7_COMP1         ((uint8_t)0x07)  /*!< COMP1 Alternate Function mapping */
#define GPIO_AF7_COMP2         ((uint8_t)0x07)  /*!< COMP2 Alternate Function mapping */
#define GPIO_AF7_EVENTOUT      ((uint8_t)0x07)  /*!< EVENTOUT Alternate Function mapping */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)




typedef enum
{
  OK       = 0x00U,
  BIT_ERROR    = 0x01U,
  BUSY     = 0x02U,
  TIMEOUT  = 0x03U
} StatusTypeDef;



typedef struct
{
  uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins */

  uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode */

  uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull */

  uint32_t Speed;      /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref GPIO_speed */

  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins
                            This parameter can be a value of @ref GPIOEx_Alternate_function_selection */
} GPIO_InitTypeDef;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
  * @{
  */
/** @defgroup GPIO_pins GPIO pins
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK              (0x0000FFFFu) /* PIN mask for assert test */
/**
  * @}
  */

/** @defgroup GPIO_mode GPIO mode
  * @brief GPIO Configuration Mode
  *        Elements values convention: 0x00WX00YZ
  *           - W  : EXTI trigger detection on 3 bits
  *           - X  : EXTI mode (IT or Event) on 2 bits
  *           - Y  : Output type (Push Pull or Open Drain) on 1 bit
  *           - Z  : GPIO mode (Input, Output, Alternate or Analog) on 2 bits
  * @{
  */
#define GPIO_MODE_INPUT                 MODE_INPUT                                                  /*!< Input Floating Mode                                                */
#define GPIO_MODE_OUTPUT_PP             (MODE_OUTPUT | OUTPUT_PP)                                   /*!< Output Push Pull Mode                                              */
#define GPIO_MODE_OUTPUT_OD             (MODE_OUTPUT | OUTPUT_OD)                                   /*!< Output Open Drain Mode                                             */
#define GPIO_MODE_AF_PP                 (MODE_AF | OUTPUT_PP)                                       /*!< Alternate Function Push Pull Mode                                  */
#define GPIO_MODE_AF_OD                 (MODE_AF | OUTPUT_OD)                                       /*!< Alternate Function Open Drain Mode                                 */
#define GPIO_MODE_ANALOG                MODE_ANALOG                                                 /*!< Analog Mode                                                        */
#define GPIO_MODE_IT_RISING             (MODE_INPUT | EXTI_IT | TRIGGER_RISING)                     /*!< External Interrupt Mode with Rising edge trigger detection         */
#define GPIO_MODE_IT_FALLING            (MODE_INPUT | EXTI_IT | TRIGGER_FALLING)                    /*!< External Interrupt Mode with Falling edge trigger detection        */
#define GPIO_MODE_IT_RISING_FALLING     (MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define GPIO_MODE_EVT_RISING            (MODE_INPUT | EXTI_EVT | TRIGGER_RISING)                    /*!< External Event Mode with Rising edge trigger detection             */
#define GPIO_MODE_EVT_FALLING           (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING)                   /*!< External Event Mode with Falling edge trigger detection            */
#define GPIO_MODE_EVT_RISING_FALLING    (MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING)  /*!< External Event Mode with Rising/Falling edge trigger detection     */
/**
  * @}
  */

/** @defgroup GPIO_speed GPIO speed
  * @brief GPIO Output Maximum frequency
  * @{
  */
#define GPIO_SPEED_FREQ_LOW             0x00000000u  /*!< Low speed       */
#define GPIO_SPEED_FREQ_MEDIUM          0x00000001u  /*!< Medium speed    */
#define GPIO_SPEED_FREQ_HIGH            0x00000002u  /*!< High speed      */
#define GPIO_SPEED_FREQ_VERY_HIGH       0x00000003u  /*!< Very high speed */
/**
  * @}
  */

/** @defgroup GPIO_pull GPIO pull
  * @brief GPIO Pull-Up or Pull-Down Activation
  * @{
  */
#define GPIO_NOPULL                     0x00000000u   /*!< No Pull-up or Pull-down activation  */
#define GPIO_PULLUP                     0x00000001u   /*!< Pull-up activation                  */
#define GPIO_PULLDOWN                   0x00000002u   /*!< Pull-down activation                */




/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */
#define GPIO_MODE_Pos                           0u
#define GPIO_MODE                               (0x3uL << GPIO_MODE_Pos)
#define MODE_INPUT                              (0x0uL << GPIO_MODE_Pos)
#define MODE_OUTPUT                             (0x1uL << GPIO_MODE_Pos)
#define MODE_AF                                 (0x2uL << GPIO_MODE_Pos)
#define MODE_ANALOG                             (0x3uL << GPIO_MODE_Pos)
#define OUTPUT_TYPE_Pos                         4u
#define OUTPUT_TYPE                             (0x1uL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP                               (0x0uL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD                               (0x1uL << OUTPUT_TYPE_Pos)
#define EXTI_MODE_Pos                           16u
#define EXTI_MODE                               (0x3uL << EXTI_MODE_Pos)
#define EXTI_IT                                 (0x1uL << EXTI_MODE_Pos)
#define EXTI_EVT                                (0x2uL << EXTI_MODE_Pos)
#define TRIGGER_MODE_Pos                         20u
#define TRIGGER_MODE                            (0x7uL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING                          (0x1uL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING                         (0x2uL << TRIGGER_MODE_Pos)
/**
  * @}
  */

/** @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define IS_GPIO_PIN_ACTION(ACTION)  (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))

#define IS_GPIO_PIN(__PIN__)        ((((uint32_t)(__PIN__) & GPIO_PIN_MASK) != 0x00u) &&\
                                     (((uint32_t)(__PIN__) & ~GPIO_PIN_MASK) == 0x00u))

#define IS_GPIO_MODE(__MODE__)      (((__MODE__) == GPIO_MODE_INPUT)              ||\
                                     ((__MODE__) == GPIO_MODE_OUTPUT_PP)          ||\
                                     ((__MODE__) == GPIO_MODE_OUTPUT_OD)          ||\
                                     ((__MODE__) == GPIO_MODE_AF_PP)              ||\
                                     ((__MODE__) == GPIO_MODE_AF_OD)              ||\
                                     ((__MODE__) == GPIO_MODE_IT_RISING)          ||\
                                     ((__MODE__) == GPIO_MODE_IT_FALLING)         ||\
                                     ((__MODE__) == GPIO_MODE_IT_RISING_FALLING)  ||\
                                     ((__MODE__) == GPIO_MODE_EVT_RISING)         ||\
                                     ((__MODE__) == GPIO_MODE_EVT_FALLING)        ||\
                                     ((__MODE__) == GPIO_MODE_EVT_RISING_FALLING) ||\
                                     ((__MODE__) == GPIO_MODE_ANALOG))

#define IS_GPIO_SPEED(__SPEED__)    (((__SPEED__) == GPIO_SPEED_FREQ_LOW)    ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_MEDIUM) ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_HIGH)   ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_VERY_HIGH))

#define IS_GPIO_PULL(__PULL__)      (((__PULL__) == GPIO_NOPULL)   ||\
                                     ((__PULL__) == GPIO_PULLUP)   || \
                                     ((__PULL__) == GPIO_PULLDOWN))



/** @defgroup GPIO_Exported_Functions_Group1 Initialization/de-initialization functions
 *  @brief    Initialization and Configuration functions
 * @{
 */

/* Initialization and de-initialization functions *****************************/
void             GPIO_Config(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void             GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);



/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions
 *  @brief    IO operation functions
 * @{
 */

/* IO operation functions *****************************************************/
StatusTypeDef GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
GPIO_PinState     GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void              GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void              GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);
void              GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);


#ifdef __cplusplus
}
#endif

#endif /* STM32G0GPIO_H */
