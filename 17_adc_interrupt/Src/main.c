#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "adc.h"
#include "uart.h"

static void adc_callback(void);
void ADC_IRQHandler(void);


uint32_t sensor_val;

int main(void) {

	uart2_tx_inint();

	pa1_adc_interrupt_init();

	start_conversion();

	while(1){

	}
}


static void adc_callback(void)
{

	sensor_val = ADC1->DR;
	printf("sensor value : %d \n\r", (int)sensor_val);

}


// interrupt requrest handler
void ADC_IRQHandler(void)
{
	// check for EOC in SR
	if((ADC1->SR & EOC) != 0)
	{
		// clear flag
		ADC1->SR &= ~EOC;

		// do something
		adc_callback();
	}

}
