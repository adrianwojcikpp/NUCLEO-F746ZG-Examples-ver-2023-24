/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <math.h>
#include "keypad.h"
#include "disp.h"
#include "servo.h"
#include "led.h"
#include "input_shaping.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
KEYPAD_Handle_TypeDef hkeypad = KEYPAD_4x4_INIT_HANDLE(KEYPAD);

DISP_TM1637_HandleTypeDef hdisp1 = {
  .CLK = DIO_INIT_HANDLE(DISP_CLK),
  .DIO = DIO_INIT_HANDLE(DISP_DIO),
  .Separator = TM1637_SEP_NONE
};

SERVO_Handle_TypeDef hservo1 = {
  .PwmOut = PWM_INIT_HANDLE(&htim13, TIM_CHANNEL_1)
};

LED_WS2812_HANDLE_CONSTRUCTOR(hld1, 8, &htim1, TIM_CHANNEL_4);

INPUT_SHAPING_HandleTypeDef hrl1 = { .RateLimit = 90.0f, .Ts = 0.02f, .x_prev = 90.0f };

uint8_t tx_buffer[8];
const int tx_msg_len = 4;
unsigned int pos_ref = 90, pos_temp;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief Writes colors to LEDs based on servo position
 * @param[in/out] hled  : LED WS2812 handle
 * @param[in]     pos   : servo position in degrees (0-180)
 * @retval  None
 */
void SERVO_Position__TO__LED_WS2812_Color(unsigned int pos, LED_WS2812_Handle_TypeDef* hled)
{
  static const unsigned int max = 0x40;
  for(int i = 0; i < hled->N; i++)
  {
    float pwr = fmax(0.0f, fmin(1.0f, ((float)pos / (180.0f/hled->N)) - i));

    unsigned int R,G;
    R = pos * (pwr*max) / 180;
    G = (180-pos) * (pwr*max) / 180;
    LED_WS2812_WriteColor_RGB(hled, i, (R << 16) | (G << 8));
  }
  LED_WS2812_Update(hled);
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &huart3)
  {
    // position 0-180 degrees
    if(tx_buffer[0] == 'P' || tx_buffer[0] == 'p')
    {
      pos_temp = strtol((char*)&tx_buffer[1], 0, 10);
      pos_ref = (pos_temp > 180) ? 180 : pos_temp;
      pos_temp = pos_ref;
      DISP_TM1637_printDecUInt(&hdisp1, pos_ref);
    }
    // speed in degrees per second
    else if(tx_buffer[0] == 'S' || tx_buffer[0] == 's')
    {
      hrl1.RateLimit = (float)strtol((char*)&tx_buffer[1], 0, 10);
    }
    HAL_UART_Receive_DMA(&huart3, tx_buffer, tx_msg_len);
  }
}

/**
  * @brief  PWM Pulse finished callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == hld1.Timer)
    LED_WS2812_Callback(&hld1);
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == hservo1.PwmOut.Timer)
  {
    float pos = INPUT_SHAPING_RateLimiter(&hrl1, pos_ref);
    SERVO_Position__TO__LED_WS2812_Color(pos, &hld1);
    SERVO_WritePosition(&hservo1, pos);
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM9_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  MX_TIM13_Init();
  /* USER CODE BEGIN 2 */
  SERVO_Init(&hservo1);
  SERVO_WritePosition(&hservo1, pos_ref);

  HAL_TIM_Base_Start_IT(hservo1.PwmOut.Timer);

  DISP_TM1637_Init(&hdisp1);
  DISP_TM1637_printDecUInt(&hdisp1, pos_ref);

  SERVO_Position__TO__LED_WS2812_Color(pos_ref, &hld1);

  HAL_UART_Receive_DMA(&huart3, tx_buffer, tx_msg_len);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  char key;
  unsigned int digit_cnt = 0;
  const unsigned int digit_max = 3;

  while (1)
  {
    if((key = KEYPAD_GetKey(&hkeypad, 0)) != '\0')
    {
      // if 0-9 digit
      if(key >= '0' && key <= '9')
      {
        if(digit_cnt == 0)
          pos_temp = (key - '0');
        else
          pos_temp = pos_temp*10 + (key - '0');
        DISP_TM1637_printDecUInt(&hdisp1, pos_temp);
        digit_cnt = (digit_cnt + 1) % digit_max;
      }

      // if ENTER (D)
      if(key == 'D')
      {
        pos_ref = (pos_temp > 180) ? 180 : pos_temp;
        DISP_TM1637_printDecUInt(&hdisp1, pos_ref);
        digit_cnt = 0;
      }

      // if BACKSPACE (C)
      if(key == 'C')
      {
        pos_temp = pos_temp/10;
        digit_cnt = (digit_cnt - 1) % digit_max;
        DISP_TM1637_printDecUInt(&hdisp1, pos_temp);
      }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
