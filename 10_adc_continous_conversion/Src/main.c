#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "adc.h"
#include "uart.h"



uint32_t sensor_val;

int main(void) {

	uart2_tx_inint();

	PA1_ADC_INIT();

	start_conversion();

	while(1){
		sensor_val = adc_read();
		printf("sensor value : %d \n\r", (int)sensor_val);
	}


}
