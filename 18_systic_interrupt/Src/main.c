#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "systic.h"
#include "uart.h"

#define GPIOAEN				(1U << 0)
#define GPIOA_5				(1U << 5)

#define LED					GPIOA_5

static void systick_callback(void);
void SysTick_Handler(void);


int main(void){

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	uart2_tx_inint();
	systick_1hz_interrupt();

	while(1) {

	}

}

static void systick_callback(void)
{
	printf("A second passed !! \n\r");
	GPIOA->ODR ^= LED;
}


void SysTick_Handler(void)
{
	//do something
	systick_callback();
}
