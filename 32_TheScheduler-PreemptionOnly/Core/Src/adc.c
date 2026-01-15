#include "stm32f4xx_hal.h"

void adc_init(void)
{
	RCC->AHB1ENR |= (1U<<0); //Enable clock for GPIOA

	RCC->APB2ENR |= (1U<<8); //Enable clock for ADC1

	GPIOA->MODER |= 0xC; //1100

	//you can also do the below for the same effect
	//GPIOA->MODER = (1U<<2);
	//GPIOA->MODER = (1U<<3);


	ADC1->CR2 = 0; //SW trigger
	ADC1->SQR3 = 1; //conversion sequence starts at ch 1
	ADC1->SQR1 = 0; //conversion sequence length 1
	ADC1->CR2 |= 1; //enable ADC1


}


uint32_t read_analog_sensor(void)
{
	ADC1->CR2 |= (1U<<30); //Start conversion
	while(!(ADC1->SR & 2)){} //Wait for conversion to complete

	return ADC1->DR;


}
