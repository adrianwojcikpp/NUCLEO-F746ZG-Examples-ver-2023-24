/**
  ******************************************************************************
  * @file     : usb_hid_util.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jun 17, 2024
  * @brief    : USB HID Keyboard utilities types and functions
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "usb_hid_util.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void USB_HID_SendKeys(uint8_t mod, uint8_t keys[6])
{
  static USB_HID_KeysCodes_TypeDef keycodes;
  keycodes.MODIFIER = mod;
  memcpy(&(keycodes.KEYCODE1), keys, 6);
  USBD_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&keycodes, sizeof(keycodes));
}
