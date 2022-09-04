/*
 ================================================================================================
 Name        : fan_controller_app.c
 Author      : Amr Hassan
 Description : fan controller according to temperature
 Date        : 10/10/2021
 ================================================================================================
 */
#include<avr/io.h>
#include"lcd.h"
#include"gpio.h"
#include"pwm_timer0.h"
#include"dc_motor.h"
#include "lm35_sensor.h"
#include"adc.h"


typedef enum
{
	OFF , ON
}FAN_State;




int main (void)
{
	uint8 temp = 0;
	FAN_State state;

	ADC_ConfigType ADC_Config = {Internal , F_CPU_8};

	LCD_init(); /* initialize LCD driver */
	ADC_init( &ADC_Config ); /* initialize ADC driver */

	DcMotor_Init();/* initialize dc motor driver */




	/* Display this string "Temp =   C" only once on LCD at the first row */
	LCD_displayStringRowColumn(0,4,"Fan is   ");
	LCD_displayStringRowColumn(1,4,"Temp =    C");

	while(1)
	{

	if (state == ON)
	{
		LCD_displayStringRowColumn(0,11,"ON");

	}
	else if (state == OFF)
	{
		LCD_displayStringRowColumn(0,11,"OFF");

	}


		temp = LM35_getTemperature();

		if(temp < 30)
		        {
		            state = OFF;

		            DcMotor_Rotate(STOP, 0);
		        }
		        else if (temp >= 30)
		        {
		            state = ON;

		            LCD_displayCharacter(' ');  /* To prevent error like "ONF" to be written */

		            if(temp >= 30 && temp < 60)
		            			{
		            				DcMotor_Rotate(CW,25);
		            			}
		            			else if(temp >= 60 && temp < 90)
		            			{
		            				DcMotor_Rotate(CW,50);
		            			}
		            			else if(temp >= 90 && temp < 120)
		            			{
		            				DcMotor_Rotate(CW,75);
		            			}
		            			else if(temp >= 120)
		            			{
		            				DcMotor_Rotate(CW,100);
		            			}
		        }

		        LCD_moveCursor(1,11);

		        if(temp >= 100)
		        {
		            LCD_intgerToString(temp);
		        }
		        else
		        {
		            LCD_intgerToString(temp);
		            /* In case the digital value is two or one digits print space in the next digit place */
		            LCD_displayCharacter(' ');
		        }
		    }

}




