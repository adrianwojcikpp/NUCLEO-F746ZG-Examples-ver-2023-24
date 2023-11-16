/**
  ******************************************************************************
  * @file     : heater.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Nov 27, 2022
  * @brief    : Electric heater components driver
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "heater.h"

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
  * @brief Turns heater on
  * @param[in] hhtr   : Heater DIO handler
  * @retval None
  */
void HEATER_DIO_On(const HEATER_DIO_Handle_TypeDef* hhtr)
{
  HEATER_DIO_Write(hhtr, HEATER_ON);
}

/**
  * @brief Turns heater off
  * @param[in] hhtr   : Heater DIO handler
  * @retval None
  */
void HEATER_DIO_Off(const HEATER_DIO_Handle_TypeDef* hhtr)
{
  HEATER_DIO_Write(hhtr, HEATER_OFF);
}

/**
  * @brief Toggles heater state
  * @param[in] hhtr   : Heater DIO handler
  * @retval None
  */
void HEATER_DIO_Toggle(const HEATER_DIO_Handle_TypeDef* hhtr)
{
  DIO_Toggle(&(hhtr->Output));
}

/**
  * @brief Writes given heater state
  * @param[in] hhtr   : Heater DIO handler
  * @param[in] state  : Heater state (HEATER_OFF or HEATER_ON)
  * @retval None
  */
void HEATER_DIO_Write(const HEATER_DIO_Handle_TypeDef* hhtr, HEATER_DIO_State_TypeDef state)
{
  DIO_Write(&(hhtr->Output), (hhtr->ActiveState == HEATER_ON_HIGH) ? state : !state);
}

/**
  * @brief Reads heater state
  * @param[in] hhtr   : Heater GPIO handler
  * @retval Heater state (HEATER_OFF or HEATER_ON)
  */
HEATER_DIO_State_TypeDef HEATER_DIO_Read(const HEATER_DIO_Handle_TypeDef* hhtr)
{
  _Bool state = DIO_Read(&(hhtr->Output));
  return (hhtr->ActiveState == HEATER_ON_HIGH) ? state : !state;
}

/**
  * @brief Initialize PWM heater control
  * @param[in] hhtr   : Heater PWM handler
  * @retval None
  */
void HEATER_PWM_Init(HEATER_PWM_Handle_TypeDef* hhtr)
{
  hhtr->Output.Duty = (hhtr->ActiveState == HEATER_ON_HIGH) ? (hhtr->Output.Duty) : (100.0f - hhtr->Output.Duty);
  PWM_Init(&(hhtr->Output));
}

/**
  * @brief Write PWM duty cycle
  * @param[in/out] hhtr   : Heater PWM handler
  * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
  * @retval None
  */
void HEATER_PWM_WriteDuty(HEATER_PWM_Handle_TypeDef* hhtr, float duty)
{
  hhtr->Output.Duty = (hhtr->ActiveState == HEATER_ON_HIGH) ? (duty) : (100.0f - duty);
  PWM_WriteDuty(&(hhtr->Output), hhtr->Output.Duty);
}

/**
  * @brief Set PWM duty cycle
  * @param[in] hhtr   : Heater PWM handler
  * @retval PWM duty cycle in percents (0. - 100.)
  */
float HEATER_PWM_ReadDuty(const HEATER_PWM_Handle_TypeDef* hhtr)
{
  return (hhtr->ActiveState == HEATER_ON_HIGH) ? (hhtr->Output.Duty) : (100.0f - hhtr->Output.Duty);
}
