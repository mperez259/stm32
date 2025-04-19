#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "systic.h"
#include "uart.h"
#include "timer.h"

#define GPIOAEN				(1U << 0)
#define GPIOA_5				(1U << 5)

#define LED					GPIOA_5


int timestamp = 0;

//set up: connect jumper wire from pa5 to pa6

int main(void) {

	tim2_pa5_output_compare();
	tim3_pa6_input_capture();

	while(1) {

		// check timer status register for capture/comp interrupt flag CC1IF by polling
		while(!(TIM3->SR & SR_CC1IF )) {}

		// read captured value
		timestamp = TIM3->CCR1;

	}
}
