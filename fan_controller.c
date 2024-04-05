/******************************************************************************
 *
 * Module: Fan Controller
 *
 * File Name: fan_controller.c
 *
 * Description: Source file for the Fan_Controller driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/
#include "dc_motor.h"
#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "pwm.h"

uint8 temp; // global variable to store the temperature from the sensor

int main(void){

	/* Create configuration structure for ADC driver */
	ADC_ConfigType ADC_Configurations = {INTERNAL_2_56V,F_CPU_8};
	ADC_init(&ADC_Configurations);
	LCD_init();
	DcMotor_Init();
	PWM_Timer0_Start(0);

	while(1){
		temp=LM35_getTemperature();

		LCD_moveCursor(0, 3);
		LCD_displayString("Fan is ");
		LCD_moveCursor(1, 2);
		LCD_displayString("TEMP =     C");


		LCD_moveCursor(1, 9);
		LCD_intgerToString(temp);


		if(temp < 30){
			LCD_moveCursor(0, 11);
			LCD_displayString("OFF");
			DcMotor_Rotate(STOP,0);


		}

		 if((temp >= 30) && (temp< 60)){
			LCD_moveCursor(0, 13);
			LCD_displayString(" "); // to delete the second F from OFF to display ON
			LCD_moveCursor(0, 11);
			LCD_displayString("ON");
			DcMotor_Rotate(CW,25);
		}
		 if((temp >= 60 ) && (temp<90)){
			LCD_moveCursor(0, 11);
			LCD_displayString("ON");
			DcMotor_Rotate(CW,50);
		}
		 if((temp >=90) && (temp<120)){
			LCD_moveCursor(0, 11);
			LCD_displayString("ON");
			DcMotor_Rotate(CW,75);
		}
		 if (temp >= 120){
			LCD_moveCursor(0, 11);
			LCD_displayString("ON");
			DcMotor_Rotate(CW,100);
		}

	}
}
