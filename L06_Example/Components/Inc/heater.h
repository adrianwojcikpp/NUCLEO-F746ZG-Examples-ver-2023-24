/**
  ******************************************************************************
  * @file		  : heater.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date     : Nov 27, 2022
  * @brief    : Electric heater components driver
  *
  ******************************************************************************
  */
#ifndef INC_HEATER_H_
#define INC_HEATER_H_

/* Public includes -----------------------------------------------------------*/
#include "dio.h"
#include "pwm.h"

/* Public typedef ------------------------------------------------------------*/
typedef enum { HEATER_ON_LOW, HEATER_ON_HIGH } HEATER_ActiveState_TypeDef;
typedef enum { HEATER_OFF = 0, HEATER_ON = 1} HEATER_DIO_State_TypeDef;

/**
  * @brief Digital output (On/Off) HEATER handle structure definition
  */
typedef struct {
  DIO_Handle_TypeDef Output;
  HEATER_ActiveState_TypeDef ActiveState;
} HEATER_DIO_Handle_TypeDef;

/**
  * @brief PWM output (0.-100.%) HEATER handle structure definition
  */
typedef struct {
  PWM_Handle_TypeDef Output;
  HEATER_ActiveState_TypeDef ActiveState;
} HEATER_PWM_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
/**
  * @brief Digital output (On/Off) heater handle structure initialization
  * @param[in] USER_NAME    : Pin user label set up in CubeMX (.ioc file)
  * @param[in] ACTIVE_STATE : Active state (polarity) of HEATER
  *       This parameter can be one of the following values:
  *            @arg HEATER_ON_LOW  : Heater turns on if output state is 0
  *            @arg HEATER_ON_HIGH : Heater turns on if output state is 1
  */
#define HEATER_DIO_INIT_HANDLE(USER_NAME, ACTIVE_STATE)	\
  { 												                          \
    .Output = DIO_INIT_HANDLE(USER_NAME),             \
    .ActiveState = ACTIVE_STATE					              \
  }

/**
  * @brief @brief PWM output (0.-100.%) heater handle structure initialization
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
  * @param[in] ACTIVE_STATE : Active state (polarity) of HEATER
  *       This parameter can be one of the following values:
  *            @arg HEATER_ON_LOW  : Heater turns on if output state is 0
  *            @arg HEATER_ON_HIGH : Heater turns on if output state is 1
  */
#define HEATER_PWM_INIT_HANDLE(TIMER, CHANNEL, ACTIVE_STATE)  \
  {                                                        \
    .Output = PWM_INIT_HANDLE((TIMER), CHANNEL),           \
    .ActiveState = ACTIVE_STATE                            \
  }

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
  * @brief Turns heater on
  * @param[in] hhtr		: Heater DIO handler
  * @retval None
  */
void HEATER_DIO_On(const HEATER_DIO_Handle_TypeDef* hhtr);

/**
  * @brief Turns heater off
  * @param[in] hhtr		: Heater DIO handler
  * @retval None
  */
void HEATER_DIO_Off(const HEATER_DIO_Handle_TypeDef* hhtr);

/**
  * @brief Toggles heater state
  * @param[in] hhtr		: Heater DIO handler
  * @retval None
  */
void HEATER_DIO_Toggle(const HEATER_DIO_Handle_TypeDef* hhtr);

/**
  * @brief Writes given heater state
  * @param[in] hhtr		: Heater DIO handler
  * @param[in] state 	: Heater state (HEATER_OFF or HEATER_ON)
  * @retval None
  */
void HEATER_DIO_Write(const HEATER_DIO_Handle_TypeDef* hhtr, HEATER_DIO_State_TypeDef state);

/**
  * @brief Reads heater state
  * @param[in] hhtr		: Heater DIO handler
  * @retval	Heater state (HEATER_OFF or HEATER_ON)
  */
HEATER_DIO_State_TypeDef HEATER_DIO_Read(const HEATER_DIO_Handle_TypeDef* hhtr);

/**
  * @brief Initialize PWM heater control
  * @param[in/out] hhtr   : Heater PWM handler
  * @retval None
  */
void HEATER_PWM_Init(HEATER_PWM_Handle_TypeDef* hhtr);

/**
  * @brief Write PWM duty cycle
  * @param[in/out] hhtr   : Heater PWM handler
  * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
  * @retval None
  */
void HEATER_PWM_WriteDuty(HEATER_PWM_Handle_TypeDef* hhtr, float duty);

/**
  * @brief Set PWM duty cycle
  * @param[in] hhtr   : Heater PWM handler
  * @retval PWM duty cycle in percents (0. - 100.)
  */
float HEATER_PWM_ReadDuty(const HEATER_PWM_Handle_TypeDef* hhtr);

#endif /* INC_HEATER_H_ */
