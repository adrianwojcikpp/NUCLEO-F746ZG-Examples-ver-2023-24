/**
  ******************************************************************************
  * @file		: serial_api_config.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Serial API configuration file
  *
  ******************************************************************************
  */

#ifndef INC_SERIAL_API_CONFIG_H_
#define INC_SERIAL_API_CONFIG_H_

/* Public includes -----------------------------------------------------------*/
#include "serial_api.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/
#define SERIAL_API_LED_MSG_LEN 4

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern SERIAL_API_LED_TypeDef hleds[3];

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_SERIAL_API_CONFIG_H_ */
