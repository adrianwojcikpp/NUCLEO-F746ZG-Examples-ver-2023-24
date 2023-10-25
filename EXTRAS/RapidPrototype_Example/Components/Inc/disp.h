/**
  ******************************************************************************
  * @file     : disp.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 4-Nov-2020
  * @brief    : Simple 4 x 8 segment LED display driver library.
  *             DISP_DIO - common anode display without internal driver
  *             DISP_TM1637 - display with internal TM1635 driver
  ******************************************************************************
  */
#ifndef INC_DISP_H_
#define INC_DISP_H_

/* Public includes -----------------------------------------------------------*/
#include <stdint.h>
#include "dio.h"

/* Public define -------------------------------------------------------------*/
#define DISP_SEG_NO 7  //!< Without decimal point segment
#define DISP_DIG_NO 4

/* Public typedef ------------------------------------------------------------*/
typedef enum {
  DISP_DP_1 = 0, DISP_DP_2, DISP_DP_3, DISP_DP_4, DISP_NONE
} DISP_DP_TypeDef;

typedef struct {
  // Display GPIO ports and pins
  DIO_Handle_TypeDef DigitOutput[DISP_DIG_NO];
  DIO_Handle_TypeDef SegmentOutput[DISP_SEG_NO];
  DIO_Handle_TypeDef DecimalPointOutput;
  // Display data
  uint8_t DataArray[DISP_DIG_NO];
  DISP_DP_TypeDef  DecimalPoint;
} DISP_DIO_HandleTypeDef;

typedef enum {
  TM1637_SEP_NONE = 0, TM1637_SEP_COLON
} TM1637_Separator_TypeDef;

typedef struct {
  DIO_Handle_TypeDef DIO;
  DIO_Handle_TypeDef CLK;
  TM1637_Separator_TypeDef Separator;
} DISP_TM1637_HandleTypeDef;

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
 * @brief Selecting decimal point position
 * @param[out] hdisp : Display handler
 * @param[in]  dp    : Decimal point position
 *       This parameter can be one of the following values:
 *            @arg DISP_DP_1 : Decimal point is enabled on first section (most significant digit)
 *            @arg DISP_DP_2 : Decimal point is enabled on second section
 *            @arg DISP_DP_3 : Decimal point is enabled on third section
 *            @arg DISP_DP_4 : Decimal point is enabled on fourth section (least significant digit)
 *            @arg DISP_NONE : Decimal point is disabled
 */
void DISP_DIO_EnableDecimalPoint(DISP_DIO_HandleTypeDef* hdisp, DISP_DP_TypeDef dp);

/**
 * @brief Write a non-negative decimal number on display.
 * @param[out] hdisp : Display handler
 * @param[in]  dec   : Non-negative decimal number, max. 4 digits
 */
void DISP_DIO_printDecUInt(DISP_DIO_HandleTypeDef* hdisp, uint16_t dec);

/**
 * @brief Display refresh routine. Should be executed at least 120 times per second.
 * @param[in] hdisp : Display handler
 */
void DISP_DIO_ROUTINE(DISP_DIO_HandleTypeDef* hdisp);

/**
 * @brief TM1637 LED display initialization procedure.
 * @note Brighthness set to 2
 * @param[in] hdisp : Display handler
 * @return None
 */
void DISP_TM1637_Init(DISP_TM1637_HandleTypeDef* hdisp);

/**
 * @brief Write a non-negative decimal number on display.
 * @param[in] hdisp : Display handler
 * @param[in] dec   : Non-negative decimal number, max. 4 digits
 * @return None
 */
void DISP_TM1637_printDecUInt(DISP_TM1637_HandleTypeDef* hdisp, uint16_t dec);

/**
 * @brief Set display brightness.
 * @param[in] hdisp      : Display handler
 * @param[in] brightness : Brightness value: <0, 8>. 0 = display off.
 * @return None
 */
void DISP_TM1637_SetBrightness(DISP_TM1637_HandleTypeDef* hdisp, uint8_t brightness);

#endif /* INC_DISP_H_ */
