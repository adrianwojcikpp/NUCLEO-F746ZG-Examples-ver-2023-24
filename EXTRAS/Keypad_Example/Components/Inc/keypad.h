/**
  ******************************************************************************
  * @file		: keypad.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 23, 2023
  * @brief   	: Keypad 4x4 (0-9, A-D, *, #)
  *
  ******************************************************************************
  */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

/* Public includes -----------------------------------------------------------*/
#include "btn.h"

/* Public define -------------------------------------------------------------*/
#define KEYPAD_ROWS_N 4
#define KEYPAD_COLS_N 4

/* Public typedef ------------------------------------------------------------*/
typedef struct {
	BTN_DIO_Handle_TypeDef Keys[KEYPAD_ROWS_N][KEYPAD_COLS_N];
	DIO_Handle_TypeDef SelectColumn[KEYPAD_COLS_N];
	char KeyValue;
	unsigned int ActiveColum;
} KEYPAD_Handle_TypeDef;

/* Public macro --------------------------------------------------------------*/
/**
 * @brief Keypad initialization with GPIO user labels.
 * @note Assumed naming convention as following:
 *       4x GPIO Outputs labels <<KEYPAD_NAME>>_COLS1, <KEYPAD_NAME>>_COLS2, etc.
 *       4x GPIO Inputs labels <<KEYPAD_NAME>>_ROWS1, <KEYPAD_NAME>>_ROWS2, etc.
 */
#define KEYPAD_4x4_INIT_HANDLE(USER_NAME) \
		    {                                 \
          .Keys = {                       \
        		  {                           \
        	      BTN_DIO_INIT_HANDLE(USER_NAME##_ROW1, BTN_PULL_UP),  \
        	      BTN_DIO_INIT_HANDLE(USER_NAME##_ROW1, BTN_PULL_UP),  \
        		    BTN_DIO_INIT_HANDLE(USER_NAME##_ROW1, BTN_PULL_UP),  \
        	      BTN_DIO_INIT_HANDLE(USER_NAME##_ROW1, BTN_PULL_UP)   \
        		  },                                                     \
              {                                                      \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW2, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW2, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW2, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW2, BTN_PULL_UP)   \
              },                                                     \
              {                                                      \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW3, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW3, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW3, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW3, BTN_PULL_UP)   \
              },                                                     \
              {                                                      \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW4, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW4, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW4, BTN_PULL_UP),  \
                BTN_DIO_INIT_HANDLE(USER_NAME##_ROW4, BTN_PULL_UP)   \
              }                                   \
          },                                      \
          .SelectColumn = {                       \
              DIO_INIT_HANDLE(USER_NAME##_COL1),  \
              DIO_INIT_HANDLE(USER_NAME##_COL2),  \
              DIO_INIT_HANDLE(USER_NAME##_COL3),  \
              DIO_INIT_HANDLE(USER_NAME##_COL4)   \
          },                 \
          .KeyValue = '\0',  \
		      .ActiveColum = 0,  \
        }

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Gets pressed key from keypad.
 * @param[in/out] hkeypad : keypad handler
 * @param[in]     delay   : delay for each column of keypad
 * @retval Pressed key character or null-character if none press was detected
 */
char KEYPAD_GetKey(KEYPAD_Handle_TypeDef* hkeypad, uint32_t delay);

#endif /* INC_KEYPAD_H_ */
