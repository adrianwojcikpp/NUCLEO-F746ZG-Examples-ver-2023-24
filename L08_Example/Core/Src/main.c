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
#include "dac.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "aio.h"
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctype.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
  float Amplitude;
  float Phase;      // [rad]
  float Mean;
  float Frequency;  // [Hz]
  float SampleTime; // [s]
} SINE_WAVE_TypeDef;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rx_buffer[8];
const uint16_t rx_msg_len = 5;
SINE_WAVE_TypeDef sine_wave = {
    .Amplitude = 1000,  /* mV */
    .Phase = 0*M_PI,    /* rad */
    .Frequency = 10,    /* Hz  */
    .Mean = 1000,       /* mV */
    .SampleTime = 0.001 /* s */
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/**
 * @brief Writes to DAC data holding register (Channel #1, 12 bits, right alignment).
 * @param[in] voltage_mV : Voltage expressed in millivolts, in range <0 - 3300> mV
 * @retval None
 */
void DAC_SetVoltage(float voltage_mV);

/**
 * @brief Computes value of given sine wave at given discrete time.
 * @param[in] sine_wave     : Structure with sine wave parameters.
 * @param[in] discrete_time : Discrete time (sample number).
 * @retval Sine wave value at discrete time.
 */
float SINE_WAVE_ReadValue(const SINE_WAVE_TypeDef* sine_wave, unsigned int discrete_time);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &huart3)
  {
    if(tolower(rx_buffer[0]) == 'a')
    {
      float amplitude = (float)strtol((char*)&rx_buffer[1], NULL, 10);
      sine_wave.Amplitude = __SATURATION(amplitude, 0.0f, DAC_VOLTAGE_MAX / 2.0f);

    }
    else if(tolower(rx_buffer[0]) == 'm')
    {
      float mean = (float)strtol((char*)&rx_buffer[1], NULL, 10);
      sine_wave.Mean = __SATURATION(mean, 0.0f, DAC_VOLTAGE_MAX / 2.0f);
    }

    HAL_UART_Receive_IT(&huart3, rx_buffer, rx_msg_len);
  }
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == &htim7)
  {
    static unsigned long int time = 0;
    float voltage_mV = SINE_WAVE_ReadValue(&sine_wave, time);
    DAC_SetVoltage(voltage_mV);
    time++;
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
  MX_USART3_UART_Init();
  MX_DAC_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim7);
  HAL_UART_Receive_IT(&huart3, rx_buffer, rx_msg_len);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

/**
 * @brief Writes to DAC data holding register (Channel #1, 12 bits, right alignment).
 * @param[in] voltage_mV : Voltage expressed in millivolts, in range <0 - 3300> mV
 * @retval None
 */
void DAC_SetVoltage(float voltage_mV)
{
  float voltage_sat_mV = DAC_VOLTAGE_SAT(voltage_mV);
  uint16_t dac_reg = DAC_VOLTAGE2REG(voltage_sat_mV);
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_reg);
}

/**
 * @brief Computes value of given sine wave at given discrete time.
 * @param[in] sine_wave     : Structure with sine wave parameters.
 * @param[in] discrete_time : Discrete time (sample number).
 * @retval Sine wave value at discrete time.
 */
float SINE_WAVE_ReadValue(const SINE_WAVE_TypeDef* sine_wave, unsigned int discrete_time)
{
  float time = sine_wave->SampleTime*discrete_time;
  float value = (sine_wave->Amplitude)*sinf(2.0f*M_PI*sine_wave->Frequency*time + sine_wave->Phase) + sine_wave->Mean;
  return value;
}

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
