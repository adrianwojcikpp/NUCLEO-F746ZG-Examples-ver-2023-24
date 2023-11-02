/**
  ******************************************************************************
  * @file     : pwm.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Nov 27, 2022
  * @brief    : Pulse Width Modulation outputs components driver.
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "pwm.h"

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
  * @brief Initialize PWM output
  * @param[in/out] hpwm   : PWM output handler
  * @retval None
  */
void PWM_Init(PWM_Handle_TypeDef* hpwm)
{
  // TODO: implement initialization with HAL
}

/**
  * @brief Write PWM duty cycle
  * @param[in/out] hpwm   : PWM output handler
  * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
  * @retval None
  */
void PWM_WriteDuty(PWM_Handle_TypeDef* hpwm, float duty)
{
  // TODO: implement duty control with HAL

  // Saturate duty cycle value

  // Write duty to handle field

  // Compute Capture/Compare Register value

  // Write value to register

}

/**
  * @brief Set PWM duty cycle
  * @param[in]     hpwm   : PWM output handler
  * @retval PWM duty cycle in percents (0. - 100.)
  */
float PWM_ReadDuty(const PWM_Handle_TypeDef* hpwm)
{
  return hpwm->Duty;
}
