/**
  ******************************************************************************
  * @file		: btn_config.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Button & switch components configuration file
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "btn.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
BTN_DIO_Handle_TypeDef pad_key_up = BTN_DIO_INIT_HANDLE(USER_IN1, BTN_PULL_DOWN);
BTN_DIO_Handle_TypeDef pad_key_down = BTN_DIO_INIT_HANDLE(USER_IN2, BTN_PULL_DOWN);
BTN_DIO_Handle_TypeDef pad_key_left = BTN_DIO_INIT_HANDLE(USER_IN3, BTN_PULL_DOWN);
BTN_DIO_Handle_TypeDef pad_key_right = BTN_DIO_INIT_HANDLE(USER_IN4, BTN_PULL_DOWN);

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
