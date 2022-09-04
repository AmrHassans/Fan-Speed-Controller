/******************************************************************************\
 *Module: DC Motor                                                            *
 *File Name: dc_motor.c                                                       *
 *Description: Source file for the AVR DC Motor driver                        *
 *Author: Amr Hassan                                                          *
\******************************************************************************/

#include"dc_motor.h"
#include"gpio.h"
#include"pwm_timer0.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void DcMotor_Init(void)
{

	/*  The Function responsible for setup the direction for the two motor pins through the GPIO driver.	 */
	GPIO_setupPinDirection(DC_MOTOR__PORT_ID, DC_MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR__PORT_ID, DC_MOTOR_IN2_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR__PORT_ID, DC_MOTOR_E_PIN_ID, PIN_OUTPUT);



	/* Stop at the DC-Motor at the beginning through the GPIO driver. */
	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);


}


void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	uint8 duty_cycle = ((float)speed/100) * 255;

	PWM_Timer0_start(duty_cycle);

	switch(state)
	{
	case STOP:

		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);

		break;
	case CW:

		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_HIGH);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
		break;
	case A_CW:

		GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);
		break;
	}



}



