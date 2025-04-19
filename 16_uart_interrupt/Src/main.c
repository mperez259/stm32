#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "systic.h"
#include "uart.h"
#include "timer.h"
#include "exti.h"

#define GPIOAEN				(1U << 0)
#define GPIOA_5				(1U << 5)

#define LED					GPIOA_5

	// fnc prototype
void USART2_IRQHandler(void);
void uart_callback(void);

char key;

int main(void) {

	// enable clock access to GPIOA and GPIOC
	RCC->AHB1ENR |= GPIOAEN;

	// set PA5 as output pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~ (1U << 11);

	// initialize uart interrupt
	uart2_rx_interrupt_init();

	while(1) {

	}
}

void uart_callback(void)
{
	key = USART2->DR;
	if(key == '1'){
				GPIOA->ODR |= LED;
			}else{
				GPIOA->ODR &= ~LED;
			}
}

void USART2_IRQHandler(void)
{
	// check if RXNE is set
	if(USART2->SR & SR_RXNE)
	{
		// do something
		uart_callback();
	}
}
