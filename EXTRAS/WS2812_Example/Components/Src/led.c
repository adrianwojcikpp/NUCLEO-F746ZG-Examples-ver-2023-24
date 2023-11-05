/**
  ******************************************************************************
  * @file		  : led.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.4.0
  * @date    	: Nov 04, 2023
  * @brief   	: + WS2812 LED controller
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "led.h"

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
 * @brief Writes given color in GBR system to selected LED in WS2812 LED line.
 * @param[in/out] hled  : LED WS2812 handle
 * @param[in]     index : LED index in LED line in range <0, (hled->N-1)> (zero based)
 * @param[in]     color : 24-bit GRB color
 * @retval  None
 */
void LED_WS2812_WriteColor_GRB(LED_WS2812_Handle_TypeDef* hled, unsigned int index, unsigned int color)
{
  if(index >= hled->N)
    return;

  for(int i = (WS2812_BITS_PER_LED-1); i >= 0; i--)
  {
    if(color & (1u << i))
      hled->DMA_Data[(index+1)*WS2812_BITS_PER_LED - 1 - i] = WS2812_BIT_HIGH;
    else
      hled->DMA_Data[(index+1)*WS2812_BITS_PER_LED - 1 - i] = WS2812_BIT_LOW;
  }
}

/**
 * @brief Writes given color in RGB system to selected LED in WS2812 LED line.
 * @param[in/out] hled  : LED WS2812 handle
 * @param[in]     index : LED index in LED line in range <0, (hled->N-1)> (zero based)
 * @param[in]     color : 24-bit RGB color
 * @retval  None
 */
void LED_WS2812_WriteColor_RGB(LED_WS2812_Handle_TypeDef* hled, unsigned int index, unsigned int color)
{
  // Ignore LSB of each color
  // TODO: investigate this bug
  color = ((0xfe & (color >> 16)) << 8) /* R */ | ((0xfe & (color >> 8)) << 16) /* G */ | (0xfe & color) /* B */;
  //color = ((0xff & (color >> 16)) << 8) /* R */ | ((0xff & (color >> 8)) << 16) /* G */ | (0xff & color) /* B */;
  LED_WS2812_WriteColor_GRB(hled, index, color);
}

/**
 * @brief Starts DMA transfer of WS2812 LED line control signal.
 * @param[in/out] hled  : LED WS2812 handle
 * @retval  None
 */
void LED_WS2812_Update(LED_WS2812_Handle_TypeDef* hled)
{
  HAL_TIM_PWM_Start_DMA(hled->Timer, hled->Channel, (uint32_t*)hled->DMA_Data, 24*(hled->N));
}

/**
 * @brief Starts DMA transfer of WS2812 LED line control signal.
 * @note  Should be called in 'HAL_TIM_PWM_PulseFinishedCallback' e.g.:
 *
 *          if(htim == hmyled.Timer)
 *            LED_WS2812_Callback(&hmyled);
 *
 * @param[in/out] hled  : LED WS2812 handle
 * @retval  None
 */
void LED_WS2812_Callback(LED_WS2812_Handle_TypeDef* hled)
{
  HAL_TIM_PWM_Stop_DMA(hled->Timer, hled->Channel);
}
