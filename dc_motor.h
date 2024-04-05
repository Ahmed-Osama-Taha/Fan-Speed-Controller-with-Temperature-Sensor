/******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC_Motor driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	STOP,CW,A_CW
}DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 * Inputs: None
 * Return: None
 */
void DcMotor_Init(void);

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 * Inputs:
 * state: The required DC Motor state, it should be CW or A-CW or stop.  DcMotor_State data type should be declared as enum or uint8.
 * speed: decimal value for the required motor speed, it should be from
   0 → 100. For example, if the input is 50, The motor should rotate with
   50% of its maximum speed.
 * Return: None
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
