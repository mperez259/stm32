#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "systic.h"
#include "uart.h"
#include "timer.h"

#define GPIOAEN				(1U << 0)
#define GPIOA_5				(1U << 5)

#define LED					GPIOA_5

int main(void) {

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	uart2_tx_inint();
	tim2_1hz_init();

	while(1) {

		// wait for SR UIF flag
		while(!(TIM2->SR & SR_UIF)) {} // keep polling until it sets

		// clear SR UIF
		TIM2->SR &= ~SR_UIF;

		printf("A second passed !! \n\r");
		GPIOA->ODR ^= LED;

	}
}
