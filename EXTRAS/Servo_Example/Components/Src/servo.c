/**
  ******************************************************************************
  * @file		  : __template.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: COMPONENT SOURCE FILE TEMPLATE
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "servo.h"
#include "common.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define SERVO_MIN_DUTY 	2.5f
#define SERVO_MAX_DUTY 12.5f

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

void SERVO_Init(SERVO_Handle_TypeDef* hservo)
{
	SERVO_WritePosition(hservo, 90.0f);
	PWM_Init(&(hservo->PwmOut));
}

void SERVO_WritePosition(SERVO_Handle_TypeDef* hservo, float pos)
{
	hservo->Position = __SATURATION(pos, 0.0f, 180.0f);
	float duty = __LINEAR_TRANSFORM(hservo->Position, 0.0f, 180.0f, SERVO_MIN_DUTY, SERVO_MAX_DUTY);
	PWM_WriteDuty(&(hservo->PwmOut), duty);
}

float SERVO_ReadPosition(SERVO_Handle_TypeDef* hservo)
{
	return hservo->Position;
}
