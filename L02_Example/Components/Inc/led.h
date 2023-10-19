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

#endif /* INC_LED_H_ */
