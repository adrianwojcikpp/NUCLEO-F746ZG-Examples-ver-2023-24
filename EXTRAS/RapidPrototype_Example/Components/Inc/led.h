/**
  ******************************************************************************
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.4.0
  * @date     : Nov 04, 2023
  * @brief    : + WS2812 LED controller
  *
  ******************************************************************************
  */

#ifndef INC_LED_H_
#define INC_LED_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32f7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
/**
 * @brief LED WS2812 handle structure definition
 */
#ifdef USE_HAL_DRIVER
typedef TIM_HandleTypeDef* LED_WS2812_TIM_TypeDef;
typedef uint32_t LED_WS2812_Channel_TypeDef;
#endif

typedef struct {
  LED_WS2812_TIM_TypeDef Timer;
  LED_WS2812_Channel_TypeDef Channel;
  uint16_t* DMA_Data;
  uint32_t N;
} LED_WS2812_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/
/* ARR = (APBx_TIM / 800 KHz)-1        */
/* APBx_TIM = 108 MHz   =>   ARR = 134 */
#define WS2812_BIT_LOW  20 /* (int)(.5f + (0.2f/1.25f)*(ARR+1.0f))    0.3us+/-150ns */
#define WS2812_BIT_HIGH 80 /* (int)(.5f + (0.8f/1.25f)*(ARR+1.0f))    0.8us+/-150ns */

#define WS2812_BITS_PER_LED 24

/* Public macro --------------------------------------------------------------*/
/**
 * @brief LED_WS2812 handle structure and DMA array definition macro
 * @note Intended to use in global scope.
 */
#ifdef USE_HAL_DRIVER
#define LED_WS2812_HANDLE_CONSTRUCTOR(HANDLE_NAME, LED_N, TIMER, CHANNEL) \
  uint16_t __##HANDLE_NAME##_dma[WS2812_BITS_PER_LED*(LED_N)];\
  LED_WS2812_Handle_TypeDef HANDLE_NAME = {                   \
      .Timer = (TIMER), .Channel = (CHANNEL), .N = LED_N,     \
      .DMA_Data = __##HANDLE_NAME##_dma                       \
  }
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Writes given color in GBR system to selected LED in WS2812 LED line.
 * @param[in/out] hled  : LED WS2812 handle
 * @param[in]     index : LED index in LED line in range <0, (hled->N-1)> (zero based)
 * @param[in]     color : 24-bit GRB color
 * @retval  None
 */
void LED_WS2812_WriteColor_GRB(LED_WS2812_Handle_TypeDef* hled, unsigned int index, unsigned int color);

/**
 * @brief Writes given color in RGB system to selected LED in WS2812 LED line.
 * @param[in/out] hled  : LED WS2812 handle
 * @param[in]     index : LED index in LED line in range <0, (hled->N-1)> (zero based)
 * @param[in]     color : 24-bit RGB color
 * @retval  None
 */
void LED_WS2812_WriteColor_RGB(LED_WS2812_Handle_TypeDef* hled, unsigned int index, unsigned int color);

/**
 * @brief Starts DMA transfer of WS2812 LED line control signal.
 * @param[in/out] hled  : LED WS2812 handle
 * @retval  None
 */
void LED_WS2812_Update(LED_WS2812_Handle_TypeDef* hled);

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
void LED_WS2812_Callback(LED_WS2812_Handle_TypeDef* hled);

#endif /* INC_LED_H_ */
