/******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC_Motor driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "common_macros.h"
#include "avr/io.h"
#include "gpio.h"
#include "pwm.h"


void DcMotor_Init(void){

	/* configure pin PB0 and PB1 as output pins using GPIO driver */
	GPIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN1_ID, PIN_OUTPUT);

	/* Motor is stop at the beginning */
	GPIO_writePin(PORTB_ID , PIN0_ID, LOGIC_LOW );
	GPIO_writePin(PORTB_ID , PIN1_ID, LOGIC_LOW );


}
void DcMotor_Rotate(DcMotor_State state,uint8 speed){



	switch(state){

		case STOP:
		GPIO_writePin(PORTB_ID , PIN0_ID, LOGIC_LOW );
		GPIO_writePin(PORTB_ID , PIN1_ID, LOGIC_LOW );
		break;

		case CW:
		PWM_Timer0_Start(speed);
		GPIO_writePin(PORTB_ID , PIN0_ID, LOGIC_LOW );
		GPIO_writePin(PORTB_ID , PIN1_ID, LOGIC_HIGH );
		break;

		case A_CW:
		PWM_Timer0_Start(speed);
		GPIO_writePin(PORTB_ID , PIN0_ID, LOGIC_HIGH );
		GPIO_writePin(PORTB_ID , PIN1_ID, LOGIC_LOW );
		break;

	}

}
