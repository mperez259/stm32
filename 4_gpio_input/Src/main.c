#include "stm32f4xx.h"


#define GPIOAEN				(1U << 0)
#define GPIOCEN				(1U << 2)
#define PIN13				(1U << 13)
#define PIN5				(1U << 5)
#define BTN_PIN				PIN13
#define LED_PIN				PIN5


int main(){
	// enable clock access to GPIOA and GPIOC
	RCC->AHB1ENR |= GPIOCEN;
	RCC->AHB1ENR |= GPIOAEN;

	// set PA5 as output pin
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~ (1U << 11);

	// set PC13 as input pin
	GPIOC->MODER &=~ (1U << 26); //set both bits to zero
	GPIOC->MODER &=~ (1U << 27);



	while(1){

		// check if BTN is pressed
		if(GPIOC->IDR & BTN_PIN) {
			// turn on LED
			GPIOA->BSRR = LED_PIN;
			}
		else{
			// resets pin, turns off
			GPIOA->BSRR = (1U << 21);
			}
		}
}
