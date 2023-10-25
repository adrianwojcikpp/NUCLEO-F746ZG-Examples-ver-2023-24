/**
  ******************************************************************************
  * @file		  : keypad.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date     : Oct 23, 2023
  * @brief    : Keypad 4x4 (0-9, A-D, *, #)
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "keypad.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
const char KEYPAD_LOOKUP_TABLE[KEYPAD_ROWS_N][KEYPAD_COLS_N] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Gets pressed key from keypad.
 * @param[in/out] hkeypad : keypad handler
 * @param[in]     delay   : delay for each column of keypad
 * @retval Pressed key character or null-character if none press was detected
 */
char KEYPAD_GetKey(KEYPAD_Handle_TypeDef* hkeypad, uint32_t delay)
{
  hkeypad->KeyValue = '\0';

  for(unsigned int c = 0; c < KEYPAD_COLS_N; c++)
  {
    // Disable all columns with high state
    for(unsigned int n = 0; n < KEYPAD_COLS_N; n++)
      DIO_Write(&(hkeypad->SelectColumn[n]), 1);
    // Enable active column with low state
    DIO_Write(&(hkeypad->SelectColumn[c]), 0);
    // Wait before reading
    HAL_Delay(delay);
    // Check if key press was detected for any of rows
    for(unsigned int r = 0; r < KEYPAD_ROWS_N; r++)
      if(BTN_DIO_EdgeDetected(&(hkeypad->Keys[r][c])) == BTN_PRESSED_EDGE)
        hkeypad->KeyValue = KEYPAD_LOOKUP_TABLE[r][c];
  }

  return hkeypad->KeyValue;
}
