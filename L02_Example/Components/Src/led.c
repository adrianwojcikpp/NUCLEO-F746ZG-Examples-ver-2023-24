/**
  ******************************************************************************
  * @file     : led.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.1
  * @date     : Nov 27, 2022
  * @brief    : Single-color LED components driver
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "led.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
  * @brief Turns LED on
  * @param[in] hled   : LED DIO handler
  * @retval None
  */
void LED_DIO_On(const LED_DIO_Handle_TypeDef* hled)
{
  LED_DIO_Write(hled, LED_ON);
}

/**
  * @brief Turns LED off
  * @param[in] hled   : LED DIO handler
  * @retval None
  */
void LED_DIO_Off(const LED_DIO_Handle_TypeDef* hled)
{
  LED_DIO_Write(hled, LED_OFF);
}

/**
  * @brief Toggles LED state
  * @param[in] hled   : LED DIO handler
  * @retval None
  */
void LED_DIO_Toggle(const LED_DIO_Handle_TypeDef* hled)
{
  DIO_Toggle(&(hled->Output));
}

/**
  * @brief Writes given LED state
  * @param[in] hled   : LED DIO handler
  * @param[in] state  : LED state (LED_OFF or LED_ON)
  * @retval None
  */
void LED_DIO_Write(const LED_DIO_Handle_TypeDef* hled, LED_DIO_State_TypeDef state)
{
  DIO_Write(&(hled->Output), (hled->ActiveState == LED_ON_HIGH) ? state : !state);
}

/**
  * @brief Reads LED state
  * @param[in] hled   : LED GPIO handler
  * @retval LED state (LED_OFF or LED_ON)
  */
LED_DIO_State_TypeDef LED_DIO_Read(const LED_DIO_Handle_TypeDef* hled)
{
  _Bool state = DIO_Read(&(hled->Output));
  return (hled->ActiveState == LED_ON_HIGH) ? state : !state;
}
