/**
  ******************************************************************************
  * @file     : input_shaping.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 9-Sep-2021
  * @brief    : Input (signal) shaping routines:
  *             + Rate limiter: 1st derivative saturation
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "input_shaping.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

/**
 * @brief Simple input shaping routine: rate (1st derivative) limiter
 * @param[in] hinshp : Input shaping handler 
 * @param[in] x      : Input signal
 * @return Processed output signal with limited change rate
 */
float INPUT_SHAPING_RateLimiter(INPUT_SHAPING_HandleTypeDef* hinshp, float x)
{
  float dx_limit = hinshp->RateLimit * hinshp->Ts;

  if( x - hinshp->x_prev > dx_limit )
    hinshp->x_prev += dx_limit;
  else if ( x - hinshp->x_prev < -dx_limit )
    hinshp->x_prev -= dx_limit;
  else 
    hinshp->x_prev = x;
  
  return hinshp->x_prev;
}
