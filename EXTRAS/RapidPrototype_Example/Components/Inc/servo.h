/**
  ******************************************************************************
  * @file		: servo.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 24, 2023
  * @brief   	: MG90S micro servo motor
  *
  ******************************************************************************
  */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

/* Public includes -----------------------------------------------------------*/
#include "pwm.h"

/* Public typedef ------------------------------------------------------------*/
typedef struct {
	PWM_Handle_TypeDef PwmOut;
	float Position;
} SERVO_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

void SERVO_Init(SERVO_Handle_TypeDef* hservo);

void SERVO_WritePosition(SERVO_Handle_TypeDef* hservo, float pos);

float SERVO_ReadPosition(SERVO_Handle_TypeDef* hservo);

#endif /* INC_SERVO_H_ */
