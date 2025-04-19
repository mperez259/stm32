#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "systic.h"
#include "uart.h"
#include "timer.h"

#define GPIOAEN				(1U << 0)
#define GPIOA_5				(1U << 5)

#define LED					GPIOA_5

static void tim2_callback(void);
void TIM2_IRQHandler(void);

int main(void) {

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	uart2_tx_inint();
	tim2_1hz_interrupt_init();

	while(1) {

	}
}

static void tim2_callback(void) {
	// wait for SR UIF flag
	while(!(TIM2->SR & SR_UIF)) {} // keep polling until it sets

	// clear SR UIF
	TIM2->SR &= ~SR_UIF;

	printf("A second passed !! \n\r");
	GPIOA->ODR ^= LED;
}

void TIM2_IRQHandler(void){

	// clear update flag
	TIM2->SR &= ~SR_UIF;

	// do something
	tim2_callback();
}
