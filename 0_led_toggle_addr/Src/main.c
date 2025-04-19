#include <stdint.h> //for uint32_t

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE 			(AHB1PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)
#define GPIOAEN				(1U << 0)
#define PIN5				(1U << 5)
#define LED_PIN				PIN5

#define __IO				volatile

typedef struct{
	// each one is offset by 4 bytes: need data type 32 bits
	// each each array element is 4 bytes
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;

}GPIO_TypeDef;

	// do the same for RCC reg
typedef struct{
	// need array 10+2 = 12
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;

}RCC_TypeDef;

#define RCC					((RCC_TypeDef *) RCC_BASE)
#define GPIOA				((GPIO_TypeDef *) GPIOA_BASE)

int main(void) {

	// 1. enable clock access to GPIOA
	// RCC_AHB1EN_R |= GPIOAEN
	RCC->AHB1ENR |= GPIOAEN;
	// 2. set PA5 as output
	// GPIOA_MODE_R |= (1U << 10)
	// GPIOA_MODE_R &=~ (1U << 11)
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &=~ (1U << 11);

	while(1){

		// toggle PA5 GPIOA_OD_R ^= LED_PIN;
		GPIOA->ODR ^= LED_PIN;
		// add delay
		for(int i = 0; i < 100000; i++){}

	}



}

