/**
  ******************************************************************************
  * @file    lcd_config.c
  * @author  AW
  * @version V2.0
  * @date    30-Oct-2020
  * @brief   Simple HD44780 driver library for STM32F7 configuration file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "lcd_config.h"
#include "main.h"
#include "i2c.h"

#ifdef LCD_USE_TIMER
#include "tim.h"
#endif

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
DIO_Handle_TypeDef __hlcd1_DATA[] = {
    DIO_INIT_HANDLE(LCD_D4),
    DIO_INIT_HANDLE(LCD_D5),
    DIO_INIT_HANDLE(LCD_D6),
    DIO_INIT_HANDLE(LCD_D7)
};

DIO_Handle_TypeDef __hlcd2_DATA[] = {
    DIO_INIT_HANDLE(LCD_D0),
    DIO_INIT_HANDLE(LCD_D1),
    DIO_INIT_HANDLE(LCD_D2),
    DIO_INIT_HANDLE(LCD_D3),
    DIO_INIT_HANDLE(LCD_D4),
    DIO_INIT_HANDLE(LCD_D5),
    DIO_INIT_HANDLE(LCD_D6),
    DIO_INIT_HANDLE(LCD_D7)
};

/* Public variables ----------------------------------------------------------*/
LCD_DIO_HandleTypeDef hlcd1 = {
  .DATA = __hlcd1_DATA,
  .RS = DIO_INIT_HANDLE(LCD_RS),
  .E = DIO_INIT_HANDLE(LCD_E),
  .Mode = LCD_4_BIT_MODE,
  .Timer = &htim7
};

LCD_DIO_HandleTypeDef hlcd2 = {
  .DATA = __hlcd2_DATA,
  .RS = DIO_INIT_HANDLE(LCD_RS),
  .E = DIO_INIT_HANDLE(LCD_E),
  .Mode = LCD_8_BIT_MODE,
  .Timer = &htim7
};

LCD_I2C_HandleTypeDef hlcd3 = {
    .I2C = &hi2c1,
    .Address = 0x27,  // PCF8574T (for all jumpers OPEN)
    .Timeout = 100,
    .Timer = &htim7
};

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/
