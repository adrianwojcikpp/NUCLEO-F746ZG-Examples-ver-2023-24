/**
  ******************************************************************************
  * @file		: serial_api.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Serial API: simple output control and input readout
  *
  ******************************************************************************
  */

#ifndef INC_SERIAL_API_H_
#define INC_SERIAL_API_H_

/* Public includes -----------------------------------------------------------*/
#include "led.h"

/* Public typedef ------------------------------------------------------------*/
/**
  * @brief Serial API LED control handle structure definition
  */
#define SERIAL_API_LED_ID_SIZE 8
typedef struct {
	LED_DIO_Handle_TypeDef* Led;
	char Id[SERIAL_API_LED_ID_SIZE];
	LED_DIO_State_TypeDef State;
} SERIAL_API_LED_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Serial API LED control message reading
 * @param[in] 	  msg		: Input message
 * @param[in/out] leds		: Serial API LED control structure array
 * @param[in] 	  leds_len	: Serial API LED control structure array's length
 * @retval Parsing status: 0 if successful, <0 otherwise
 */
int SERIAL_API_LED_ReadMsg(const char* msg, SERIAL_API_LED_TypeDef* leds, int leds_len);

#endif /* INC_SERIAL_API_H_ */
