/**
  ******************************************************************************
  * @file     : dio.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Nov 27, 2022
  * @brief    : Analog inputs/outputs components header.
  *
  ******************************************************************************
  */

#ifndef INC_AIO_H_
#define INC_AIO_H_

/* Public includes -----------------------------------------------------------*/
#include "common.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/
#define ADC_BIT_RES      12      // [bits]
#define ADC_REG_MAX      (float)((1ul << ADC_BIT_RES) - 1)
#define ADC_VOLTAGE_MAX  3.3f    // [V]

#define ADC1_NUMBER_OF_CONV  2
#define ADC1_TIMEOUT         1 // [ms]

/* Public macro --------------------------------------------------------------*/

/**
 * @brief ADC data register to voltage in millivolts.
 * @param[in] reg : Data register
 * @return Input voltage in millivolts
 */
#define ADC_REG2VOLTAGE(reg) (1000.0f*__LINEAR_TRANSFORM((float)reg,         \
                                                       0.0f, ADC_REG_MAX,    \
                                                       0.0f, ADC_VOLTAGE_MAX))

/**
 * @brief ADC voltage in volts to data register.
 * @param[in] vol : Output voltage in millivolts
 * @return Data register
 */
#define ADC_VOLTAGE2REG(vol) (uint16_t)(__LINEAR_TRANSFORM(vol/1000.0f, \
                                               0.0, ADC_VOLTAGE_MAX,    \
                                               0.0, ADC_REG_MAX      ))

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_AIO_H_ */
