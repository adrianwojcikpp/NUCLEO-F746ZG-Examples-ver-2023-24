/**
  ******************************************************************************
  * @file     : disp.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 4-Nov-2020
  * @brief    : Simple 4 x 8 segment LED display driver library.
  *             DISP_DIO - common anode display without internal driver
  *             DISP_TM1637 - display with internal TM1635 driver
  ******************************************************************************
  */
/* Private includes ----------------------------------------------------------*/
#include "disp.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DISP_EMPTY_CHAR   16
#define DISP_DECIMALS_NO  10
#define TM1637_CYCLES_PER_1US 216

/* Private macro -------------------------------------------------------------*/
#define __POWER_OF_TEN(n) 1e##n

/* Private variables ---------------------------------------------------------*/
const uint8_t DISP_COMMON_ANODE_MAP[] = {
  0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, // 0-9
  0x88, 0x83, 0xC6, 0xAC, 0x86, 0x8E, // A-F
  0xFF
};

const uint8_t DISP_COMMON_CATHODE_MAP[] = {
  0x3f, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, // 0-9
  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, // A-F
  0x00
};

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void __disp_dio_write_data(DISP_DIO_HandleTypeDef* hdisp, uint8_t data)
{
  for(uint8_t i = 0; i < DISP_SEG_NO; i++)
    DIO_Write(&(hdisp->SegmentOutput[i]), (data >> i) & 0x01);
}

void __disp_dio_disable_all_digits(DISP_DIO_HandleTypeDef* hdisp)
{
  for(uint8_t i = 0; i < DISP_DIG_NO; i++)
    DIO_WriteLow(&(hdisp->DigitOutput[i]));
}

void __disp_dio_enable_digit(DISP_DIO_HandleTypeDef* hdisp, uint8_t dig)
{
  if(dig < DISP_DIG_NO)
    DIO_WriteHigh(&(hdisp->DigitOutput[dig]));
}

void __disp_dio_enable_decimal_point(DISP_DIO_HandleTypeDef* hdisp)
{
  DIO_WriteLow(&(hdisp->DecimalPointOutput));
}

void __disp_dio_disable_decimal_point(DISP_DIO_HandleTypeDef* hdisp)
{
  DIO_WriteHigh(&(hdisp->DecimalPointOutput));
}

void __tm1637_delay_us(unsigned int i)
{
  for (; i>0; i--)
  {
    for (int j = 0; j < TM1637_CYCLES_PER_1US; ++j)
    {
      __asm__ __volatile__("nop\n\t":::"memory");
    }
  }
}

void __tm1637_start(DISP_TM1637_HandleTypeDef* hdisp)
{
  DIO_WriteHigh(&(hdisp->CLK));
  DIO_WriteHigh(&(hdisp->DIO));
  __tm1637_delay_us(2);
  DIO_WriteLow(&(hdisp->DIO));
}

void __tm1637_stop(DISP_TM1637_HandleTypeDef* hdisp)
{
  DIO_WriteLow(&(hdisp->CLK));
  __tm1637_delay_us(2);
  DIO_WriteLow(&(hdisp->DIO));
  __tm1637_delay_us(2);
  DIO_WriteHigh(&(hdisp->CLK));
  __tm1637_delay_us(2);
  DIO_WriteHigh(&(hdisp->DIO));
}

void __tm1637_read_result(DISP_TM1637_HandleTypeDef* hdisp)
{
  DIO_WriteLow(&(hdisp->CLK));
  __tm1637_delay_us(5);
  // while (dio); // We're cheating here and not actually reading back the response.
  DIO_WriteHigh(&(hdisp->CLK));
  __tm1637_delay_us(2);
  DIO_WriteLow(&(hdisp->CLK));
}

void __tm1637_write_byte(DISP_TM1637_HandleTypeDef* hdisp, unsigned char b)
{
  for (int i = 0; i < 8; ++i)
  {
    DIO_WriteLow(&(hdisp->CLK));
    if(b & 0x01)
    {
      DIO_WriteHigh(&(hdisp->DIO));
    }
    else
    {
      DIO_WriteLow(&(hdisp->DIO));
    }
    __tm1637_delay_us(3);
    b >>= 1;
    DIO_WriteHigh(&(hdisp->CLK));
    __tm1637_delay_us(3);
  }
}

/* Public functions ----------------------------------------------------------*/

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
void DISP_DIO_EnableDecimalPoint(DISP_DIO_HandleTypeDef* hdisp, DISP_DP_TypeDef dp)
{
  hdisp->DecimalPoint = dp;
}

/**
 * @brief Write a non-negative decimal number on display.
 * @param[out] hdisp : Display handler
 * @param[in]  dec   : Non-negative decimal number, max. 4 digits
 */
void DISP_DIO_printDecUInt(DISP_DIO_HandleTypeDef* hdisp, uint16_t dec)
{
  uint16_t div = __POWER_OF_TEN(3);
  for(uint8_t i = 0; i < DISP_DIG_NO; i++)
  {
    hdisp->DataArray[i] = dec / div;
    dec = dec % div;
    div /= 10;
  }
}

/**
 * @brief Display refresh routine. Should be executed at least 120 times per second.
 * @param[in] hdisp : Display handler
 */
void DISP_DIO_ROUTINE(DISP_DIO_HandleTypeDef* hdisp)
{
  static uint8_t dig = 0;  // active digit selector

  // Disable all segments
  __disp_dio_disable_all_digits(hdisp);

  // Enable single segment
  __disp_dio_enable_digit(hdisp, dig);

  // Write to selected segment
  uint8_t idx = hdisp->DataArray[dig];
  
  /* DECIMAL POSITIVE NUMBERS: 0000-9999 */
  if(idx < DISP_DECIMALS_NO)
    __disp_dio_write_data(hdisp, DISP_COMMON_ANODE_MAP[idx]);
  
  //else if(...) 
  /* text handling, 
     hex number handling, 
     negative decimal number handling 
     etc */
     
  /* EMPTY CHARACTER (BLANK) */
  else
    __disp_dio_write_data(hdisp, DISP_COMMON_ANODE_MAP[DISP_EMPTY_CHAR]);

  // Decimal point control
  if(hdisp->DecimalPoint == dig)
    __disp_dio_enable_decimal_point(hdisp);
  else
    __disp_dio_disable_decimal_point(hdisp);

  // Select next segment
  dig = (dig < DISP_DIG_NO-1) ? (dig+1) : (0);
}

/**
 * @brief TM1637 LED display initialization procedure.
 * @note Brighthness set to 2
 * @param[in] hdisp : Display handler
 * @return None
 */
void DISP_TM1637_Init(DISP_TM1637_HandleTypeDef* hdisp)
{
  DISP_TM1637_SetBrightness(hdisp, 2);
}

/**
 * @brief Write a non-negative decimal number on display.
 * @param[in] hdisp : Display handler
 * @param[in] dec   : Non-negative decimal number, max. 4 digits
 * @return None
 */
void DISP_TM1637_printDecUInt(DISP_TM1637_HandleTypeDef* hdisp, uint16_t dec)
{
  unsigned char digitArr[4];
  for (int i = 0; i < 4; ++i)
  {
    digitArr[i] = DISP_COMMON_CATHODE_MAP[dec % 10];
    dec /= 10;
  }
  if(hdisp->Separator == TM1637_SEP_COLON)
  {
    digitArr[2] |= (1 << 7);
  }

  __tm1637_start(hdisp);
  __tm1637_write_byte(hdisp, 0x40);
  __tm1637_read_result(hdisp);
  __tm1637_stop(hdisp);

  __tm1637_start(hdisp);
  __tm1637_write_byte(hdisp, 0xc0);
  __tm1637_read_result(hdisp);

  for (int i = 0; i < 4; ++i) {
    __tm1637_write_byte(hdisp, digitArr[3 - i]);
    __tm1637_read_result(hdisp);
  }
  __tm1637_stop(hdisp);
}

/**
 * @brief Set display brightness.
 * @param[in] hdisp      : Display handler
 * @param[in] brightness : Brightness value: <0, 8>. 0 = display off.
 * @return None
 */
void DISP_TM1637_SetBrightness(DISP_TM1637_HandleTypeDef* hdisp, uint8_t brightness)
{
  // Brightness command:
  // 1000 0XXX = display off
  // 1000 1BBB = display on, brightness 0-7
  // X = don't care
  // B = brightness
  __tm1637_start(hdisp);
  __tm1637_write_byte(hdisp, 0x87 + brightness);
  __tm1637_read_result(hdisp);
  __tm1637_stop(hdisp);
}
