#include "stm32f4xx.h"
#include "adc.h"

// choosing PA1 for ADC

#define GPIOAEN				(1U << 0)
#define ADC1EN				(1U << 8)
#define ADC_CH1				(1U << 0)
#define ADC_SEQ_LEN_1		0x00
#define ADON				(1U << 0)
#define SWSTART				(1U << 30)
#define EOC					(1U << 1)
#define CONT				(1U << 1)






void PA1_ADC_INIT(void)
{
	//------- config adc pin----------
	// enable clock access to gpioa
	RCC->AHB1ENR |= GPIOAEN;

	// set mode of PA1 to analog
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);

	//------- config adc module-------
	// enable clock access to adc
	RCC->APB2ENR |= ADC1EN;

	// configure adc parameters
	// conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	// conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	// enable adc module
	ADC1->CR2 |= ADON;
}

void start_conversion(void)
{
	// enable continous conversion
	ADC1->CR2 |= CONT;

	// start adc conversion software start bit 30
	ADC1->CR2 |= SWSTART;
}


uint32_t adc_read(void)
{
	// wait for conversion to complete
	while(!(ADC1->SR & EOC)) {}

	// read
	return (ADC1->DR);
}
