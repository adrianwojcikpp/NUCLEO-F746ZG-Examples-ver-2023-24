/**
  ******************************************************************************
  * @file		: serial_api_config.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Serial API configuration file
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "serial_api.h"
#include "led_config.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
SERIAL_API_LED_TypeDef hleds[3] = {
	{ .Id = "LD1", .Led = &hldg1, .State = LED_OFF },
	{ .Id = "LD2", .Led = &hldb1, .State = LED_OFF },
	{ .Id = "LD3", .Led = &hldr1, .State = LED_OFF },
};
/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
