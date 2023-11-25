/**
  ******************************************************************************
  * @file    lcd_config.h
  * @author  AW
  * @version V2.0
  * @date    30-Oct-2020
  * @brief   Simple HD44780 driver library for STM32F7 configuration file.
  *
  ******************************************************************************
  */
#ifndef INC_LCD_CONFIG_H_
#define INC_LCD_CONFIG_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern LCD_DIO_HandleTypeDef hlcd1;
extern LCD_DIO_HandleTypeDef hlcd2;
extern LCD_I2C_HandleTypeDef hlcd3;

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_LCD_CONFIG_H_ */
