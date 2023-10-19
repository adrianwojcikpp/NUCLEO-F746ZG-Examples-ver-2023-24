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

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
LED_DIO_Handle_TypeDef hldg1 = LED_DIO_INIT_HANDLE(LD1, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hldb1 = LED_DIO_INIT_HANDLE(LD2, LED_ON_HIGH);
LED_DIO_Handle_TypeDef hldr1 = LED_DIO_INIT_HANDLE(LD3, LED_ON_HIGH);

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
