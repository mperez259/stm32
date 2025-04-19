// interrupt when push button pressed
// push button => PC13

#include "exti.h"

#define GPIOCEN			(1U << 2)
#define SYSCFGEN		(1U << 14)
#define EXTI13			(1U << 5)
#define UNMASK			(1U << 13)
#define FALL_TRIG		(1U << 13);

void pc13_exti_init(void) {

	// disable global interrupt (good practice)
	__disable_irq();

	// enable clock access for gpioc
	RCC->AHB1ENR |= GPIOCEN;

	// enable clock access to SYSCONFIG => bus: APB2 from ref manual
	RCC->APB2ENR |= SYSCFGEN;

	// select portc for exti13 set pc13 as input
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);
	// exticr1 set to reset value: 0x00000000 by default
	SYSCFG->EXTICR[3] |= EXTI13;

	// unmask exti13
	EXTI->IMR |= UNMASK;

	// config for falling edge trigger:
	//falling trigger select register FTSR
	EXTI->FTSR |= FALL_TRIG;

	// enable exti line in NVIC for external int. NVIC is in CORE
	// EXTI_10_IRQn is in "stm32f4xx.h"
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// enable global interrupts
	__enable_irq();
}

