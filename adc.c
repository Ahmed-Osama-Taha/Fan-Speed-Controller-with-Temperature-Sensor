 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Ahmed Osama
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType *Config_ptr)

{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */


	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
 	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	SET_BIT(ADCSRA, ADEN);

		if(Config_ptr->ref_volt == VREF_TURNED_OFF)
		{
			ADMUX = 0;
		}
		else if(Config_ptr->ref_volt == AVCC)
		{
			ADMUX = 0b01000000;
		}
		else if(Config_ptr->ref_volt == RESERVED)
		{
			ADMUX = 0b10000000;
		}
		else if(Config_ptr->ref_volt == INTERNAL_2_56V)
		{
			ADMUX = 0b11000000;
		}

		if(Config_ptr->prescaler == F_CPU_2)
		{
			SET_BIT(ADCSRA, ADPS0);
			CLEAR_BIT(ADCSRA,ADPS1);
	     	CLEAR_BIT(ADCSRA,ADPS2);
		}
		else if(Config_ptr->prescaler == F_CPU_4)
		{
			SET_BIT(ADCSRA, ADPS1);
			CLEAR_BIT(ADCSRA,ADPS0);
			CLEAR_BIT(ADCSRA,ADPS2);
		}
		else if(Config_ptr->prescaler == F_CPU_8)
		{
			SET_BIT(ADCSRA, ADPS1);
			SET_BIT(ADCSRA, ADPS0);
			CLEAR_BIT(ADCSRA,ADPS2);
		}
		else if(Config_ptr->prescaler == F_CPU_16)
		{
			SET_BIT(ADCSRA, ADPS2);
			CLEAR_BIT(ADCSRA,ADPS1);
			CLEAR_BIT(ADCSRA,ADPS0);
		}
		else if(Config_ptr->prescaler == F_CPU_32)
		{
			SET_BIT(ADCSRA, ADPS2);
			CLEAR_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA, ADPS0);
		}
		else if(Config_ptr->prescaler == F_CPU_64)
		{
			SET_BIT(ADCSRA, ADPS1);
			SET_BIT(ADCSRA, ADPS2);
			CLEAR_BIT(ADCSRA,ADPS0);
		}
		else if(Config_ptr->prescaler == F_CPU_128)
		{
			SET_BIT(ADCSRA, ADPS0);
			SET_BIT(ADCSRA, ADPS1);
			SET_BIT(ADCSRA, ADPS2);
		}

}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
