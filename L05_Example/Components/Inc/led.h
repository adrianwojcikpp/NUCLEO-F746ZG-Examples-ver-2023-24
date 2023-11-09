/**
  ******************************************************************************
  * @file		  : led.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.1
  * @date     : Nov 27, 2022
  * @brief   	: Single-color LED components driver
  *
  ******************************************************************************
  */
#ifndef INC_LED_H_
#define INC_LED_H_

/* Public includes -----------------------------------------------------------*/
#include "dio.h"
#include "pwm.h"

/* Public typedef ------------------------------------------------------------*/
typedef enum { LED_ON_LOW, LED_ON_HIGH } LED_ActiveState_TypeDef;
typedef enum { LED_OFF = 0, LED_ON = 1} LED_DIO_State_TypeDef;

/**
  * @brief Digital output (On/Off) LED handle structure definition
  */
typedef struct {
  DIO_Handle_TypeDef Output;
  LED_ActiveState_TypeDef ActiveState;
} LED_DIO_Handle_TypeDef;

/**
  * @brief PWM output (0.-100.%) LED handle structure definition
  */
typedef struct {
  PWM_Handle_TypeDef Output;
  LED_ActiveState_TypeDef ActiveState;
} LED_PWM_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
/**
  * @brief Digital output (On/Off) LED handle structure initialization
  * @param[in] USER_NAME    : Pin user label set up in CubeMX (.ioc file)
  * @param[in] ACTIVE_STATE : Active state (polarity) of LED
  *       This parameter can be one of the following values:
  *            @arg LED_ON_LOW  : LED turns on if output state is 0
  *            @arg LED_ON_HIGH : LED turns on if output state is 1
  */
#define LED_DIO_INIT_HANDLE(USER_NAME, ACTIVE_STATE)	\
  { 												                          \
    .Output = DIO_INIT_HANDLE(USER_NAME),             \
    .ActiveState = ACTIVE_STATE					              \
  }

/**
  * @brief @brief PWM output (0.-100.%) LED handle structure initialization
  * @param[in] TIMER        : TIM handle
  *       This parameter can be one of the following values:
  *            @arg &htim1  : TIM1 (Advanced control timer, 6 channels)
  *            @arg &htim2  : TIM2 (General purpose timer, 4 channels)
  *            @arg &htim3  : TIM3 (General purpose timer, 4 channels)
  *            @arg &htim4  : TIM4 (General purpose timer, 4 channels)
  *            @arg &htim5  : TIM5 (General purpose timer, 4 channels)
  *            @arg &htim8  : TIM8 (Advanced control timer, 6 channels)
  *            @arg &htim9  : TIM9 (General purpose timer, 2 channels)
  *            @arg &htim10 : TIM10 (General purpose timer, 1 channel)
  *            @arg &htim11 : TIM11 (General purpose timer, 1 channel)
  *            @arg &htim12 : TIM12 (General purpose timer, 2 channels)
  *            @arg &htim13 : TIM13 (General purpose timer, 1 channel)
  *            @arg &htim14 : TIM14 (General purpose timer, 1 channel)
  * @param[in] CHANNEL      : TIM Channel
  *       This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  *            @arg TIM_CHANNEL_5: TIM Channel 5 selected
  *            @arg TIM_CHANNEL_6: TIM Channel 6 selected
  * @param[in] ACTIVE_STATE : Active state (polarity) of LED
  *       This parameter can be one of the following values:
  *            @arg LED_ON_LOW  : LED turns on if output state is 0
  *            @arg LED_ON_HIGH : LED turns on if output state is 1
  */
#define LED_PWM_INIT_HANDLE(TIMER, CHANNEL, ACTIVE_STATE)  \
  {                                                        \
    .Output = PWM_INIT_HANDLE((TIMER), CHANNEL),           \
    .ActiveState = ACTIVE_STATE                            \
  }

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
  * @brief Turns LED on
  * @param[in] hled		: LED DIO handler
  * @retval None
  */
void LED_DIO_On(const LED_DIO_Handle_TypeDef* hled);

/**
  * @brief Turns LED off
  * @param[in] hled		: LED DIO handler
  * @retval None
  */
void LED_DIO_Off(const LED_DIO_Handle_TypeDef* hled);

/**
  * @brief Toggles LED state
  * @param[in] hled		: LED DIO handler
  * @retval None
  */
void LED_DIO_Toggle(const LED_DIO_Handle_TypeDef* hled);

/**
  * @brief Writes given LED state
  * @param[in] hled		: LED DIO handler
  * @param[in] state 	: LED state (LED_OFF or LED_ON)
  * @retval None
  */
void LED_DIO_Write(const LED_DIO_Handle_TypeDef* hled, LED_DIO_State_TypeDef state);

/**
  * @brief Reads LED state
  * @param[in] hled		: LED DIO handler
  * @retval	LED state (LED_OFF or LED_ON)
  */
LED_DIO_State_TypeDef LED_DIO_Read(const LED_DIO_Handle_TypeDef* hled);

/**
  * @brief Initialize PWM LED control
  * @param[in/out] hled   : LED PWM handler
  * @retval None
  */
void LED_PWM_Init(LED_PWM_Handle_TypeDef* hled);

/**
  * @brief Write PWM duty cycle
  * @param[in/out] hled   : LED PWM handler
  * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
  * @retval None
  */
void LED_PWM_WriteDuty(LED_PWM_Handle_TypeDef* hled, float duty);

/**
  * @brief Set PWM duty cycle
  * @param[in] hled   : LED PWM handler
  * @retval PWM duty cycle in percents (0. - 100.)
  */
float LED_PWM_ReadDuty(const LED_PWM_Handle_TypeDef* hled);

#endif /* INC_LED_H_ */
