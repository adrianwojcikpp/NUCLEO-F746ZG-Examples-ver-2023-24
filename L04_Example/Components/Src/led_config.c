/**
  ******************************************************************************
  * @file		  : led_config.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.1
  * @date     : Nov 27, 2022
  * @brief   	: Single-color LED components configuration file
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "led.h"
#include "main.h"
#include "tim.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
LED_DIO_Handle_TypeDef hld1 = LED_DIO_INIT_HANDLE(LD1, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hld2 = LED_DIO_INIT_HANDLE(LD2, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hld3 = LED_DIO_INIT_HANDLE(LD3, LED_ON_HIGH);

LED_PWM_Handle_TypeDef hldr = LED_PWM_INIT_HANDLE(&htim3, TIM_CHANNEL_1, LED_ON_HIGH);
LED_PWM_Handle_TypeDef hldg = LED_PWM_INIT_HANDLE(&htim3, TIM_CHANNEL_2, LED_ON_HIGH);
LED_PWM_Handle_TypeDef hldb = LED_PWM_INIT_HANDLE(&htim3, TIM_CHANNEL_3, LED_ON_HIGH);
/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
