/**
  ******************************************************************************
  * @file     : input_shaping.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 9-Sep-2021
  * @brief    : Input (signal) shaping routines:
  *             + Rate limiter: 1st derivative saturation
  *
  ******************************************************************************
  */
#ifndef __INPUT_SHAPING_H__
#define __INPUT_SHAPING_H__  
  
/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/
typedef struct {
  float x_prev;
  float RateLimit; 
  float Ts;
} INPUT_SHAPING_HandleTypeDef;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/**
 * @brief Simple input shaping routine: rate (1st derivative) limiter
 * @param[in] hinshp : Input shaping handler 
 * @param[in] x      : Input signal
 * @return Processed output signal with limited change rate
 */
float INPUT_SHAPING_RateLimiter(INPUT_SHAPING_HandleTypeDef* hinshp, float x);

/* Public function prototypes ------------------------------------------------*/

#endif /* __INPUT_SHAPING_H__ */
