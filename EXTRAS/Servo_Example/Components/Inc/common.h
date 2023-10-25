/**
  ******************************************************************************
  * @file     : common.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Oct 24, 2023
  * @brief    : Common macros and routines.
  *
  ******************************************************************************
  */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

/* Public includes -----------------------------------------------------------*/
#include <math.h>

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
/**
 * @brief Linear transformation of 'x' from <amin, amax> to <bmin, bmax>.
 * @param[in] x Input variable
 * @param[in] amin Minimum of input range
 * @param[in] amax Maximum of input range
 * @param[in] bmin Minimum of output range
 * @param[in] bmax Maximum of output range
 * @return Scaled output variable in <bmin, bmax> range
 */
#define __LINEAR_TRANSFORM(x,amin,amax,bmin,bmax) (((x-amin)/(amax-amin))*(bmax-bmin)+bmin)

/**
 * @brief Saturation (clamping) of 'x' in range <xmax, xmin>
 * @param[in] x Input variable
 * @param[in] xmin Minimum of output range
 * @param[in] xmax Maximum of output range
 */
#define __SATURATION(x,xmin,xmax) fmaxf(fminf(x, xmax), xmin);

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_COMMON_H_ */
