/******************************************************************************\
 *Module: ADC                                                                 *
 *File Name: adc.h                                                            *
 *Description: Header file for the AVR ADC driver                             *
 *Author: Amr Hassan                                                          *
\******************************************************************************/


#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_MAXIMUM_VALUE     1023
#define ADC_REF_VOLT_VALUE    2.56

/*******************************************************************************
 *                                Decelerations                                *
 *******************************************************************************/

typedef enum
{
	AREF , AVCC , Reserved , Internal
}ADC_RefrenceVoltage;

typedef enum
{
	NO_PRESCALER , F_CPU_2 , F_CPU_4 , F_CPU_8 , F_CPU_16 , F_CPU_32, F_CPU_64 , F_CPU_128
}ADC_Prescaler;


typedef struct
{
	ADC_RefrenceVoltage ref_volt;
	ADC_Prescaler prescaler;

}ADC_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * config_ptr);

uint16 ADC_readChannel(uint8 ch_num);


#endif /* ADC_H_ */
