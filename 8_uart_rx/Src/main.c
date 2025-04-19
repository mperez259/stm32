#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"

#define GPIOAEN				(1U << 0)
#define GPIOA_5				(1U << 5)

#define LED_PIN				GPIOA_5


volatile char key;

int main(){

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	uart2_rxtx_inint();


	while(1) {
		key = uart2_read();

		if(key == '1'){
			GPIOA->ODR |= LED_PIN;
		}else{
			GPIOA->ODR &= ~LED_PIN;
		}
	}

}

