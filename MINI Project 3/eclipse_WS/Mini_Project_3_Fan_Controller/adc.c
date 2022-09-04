/******************************************************************************\
 *Module: ADC                                                                 *
 *File Name: adc.c                                                            *
 *Description: Source file for the AVR ADC driver                             *
 *Author: Amr Hassan                                                          *
\******************************************************************************/

#include "adc.h"
#include "avr/io.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void ADC_init(const ADC_ConfigType * config_ptr)
{
	/* ADMUX Register Bits Description:
		 * REFS1:0 = 11 to choose to connect Internal reference voltage with External capacitor AREF pin
		 * ADLAR   = 0 right adjusted */

	ADMUX = (ADMUX & 0X3F) | ( (config_ptr -> ref_volt) << REFS0);

	/* ADCSRA Register Bits Description:
		 * ADEN    = 1 Enable ADC
		 * ADIE    = 0 Disable ADC Interrupt
		 * ADATE   = 0 Disable Auto Trigger
		 * ADPS2:0 = 011 by using  to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
		 */

	ADCSRA = (ADCSRA & 0XF8) | ( (config_ptr -> prescaler) & 0X07 );
	SET_BIT(ADCSRA,ADEN);
	CLEAR_BIT(ADCSRA,ADIE);
}

uint16 ADC_readChannel(uint8 ch_num)
{
	ch_num &= 0x07;
	ADMUX &= 0xE0;
	ADMUX = ADMUX | ch_num ;
	SET_BIT( ADCSRA , ADSC );
	while( BIT_IS_CLEAR( ADCSRA , ADIF ) );
	SET_BIT( ADCSRA , ADIF );
	return ADC;
}
