/**
  ******************************************************************************
  * @file		: serial_api.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Serial API: simple output control and input readout
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "serial_api.h"

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Serial API LED control message reading
 * @param[in] 	  msg		: Input message
 * @param[in/out] leds		: Serial API LED control structure array
 * @param[in] 	  leds_len	: Serial API LED control structure array's length
 * @retval Parsing status: 0 if successful, <0 otherwise
 */
int SERIAL_API_LED_ReadMsg(const char* msg, SERIAL_API_LED_TypeDef* leds, int leds_len)
{
	for(int i = 0; i < leds_len; i++)
	{
		/* Message structure: 3 character ID + state as 0/1 e.g. LD11 to turn LD1 on */
		if(strncmp(leds[i].Id, msg, 3) == 0)
			leds[i].State = strtol(&msg[3], NULL, 10);
	}

	return 0;
}
