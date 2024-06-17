/**
  ******************************************************************************
  * @file     : usb_hid_util.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jun 17, 2024
  * @brief    : USB HID Keyboard utilities types and functions
  *
  ******************************************************************************
  */

#ifndef INC_USB_HID_UTIL_H_
#define INC_USB_HID_UTIL_H_

/* Public includes -----------------------------------------------------------*/
#include <stdint.h>
#include "usbd_hid.h"
#include "usb_hid_keys.h"

/* Public typedef ------------------------------------------------------------*/
typedef struct
{
  uint8_t MODIFIER;
  uint8_t RESERVED;
  uint8_t KEYCODE1;
  uint8_t KEYCODE2;
  uint8_t KEYCODE3;
  uint8_t KEYCODE4;
  uint8_t KEYCODE5;
  uint8_t KEYCODE6;
} USB_HID_KeysCodes_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern USBD_HandleTypeDef hUsbDeviceFS;

/* Public function prototypes ------------------------------------------------*/
void USB_HID_SendKeys(uint8_t mod, uint8_t keys[6]);

#endif /* INC_USB_HID_UTIL_H_ */
