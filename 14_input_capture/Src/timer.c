// using TIM2 for this one -> APB1 bus

#include "stm32f4xx.h"


#define TIM2EN		(1U << 0)
#define TIM3EN		(1U << 1)	// the next one over from TIM2

#define CR1_CEN		(1U << 0)
#define OC_TOGGLE	((1U << 4) | (1U << 5))
#define CCER_CC1E	(1U << 0)
#define GPIOAEN		(1U << 0)

#define AFR5_TIM	(1U << 20)
#define AFR6_TIM	(1U << 25)

#define CCER_CCIS	(1U << 0)



void tim2_1hz_init(void)
{
	// enable clock access to TIM2
	RCC->APB1ENR |= TIM2EN;

	// set prescale value
	TIM2->PSC = 1600-1;		// count from 0 to 1599 => 16 000 000 / 1 600 = 10k

	// set auto reload value
	TIM2->ARR = 10000-1;	// 10k/10k = 1

	// clear counter
	TIM2->CNT = 0;

	// enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim2_pa5_output_compare(void)
{
	// ---config PA5---
	// enable clk access
	RCC->AHB1ENR = GPIOAEN;

	// set pa5 to alt fcn mode to TMR2 CH1 in MODER
	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER |= (1U << 11);

	// set pa5 alt fcn type to TIM2_CH1 (AF01)
	// AFRL and AFRH in a 2 D array AFR[0] and AFR[1]
	// to set AF1 => 0001 in bits 20 to 23
	GPIOA->AFR[0] = AFR5_TIM;

	// enable clock access to TIM2
	RCC->APB1ENR |= TIM2EN;

	// set prescale value
	TIM2->PSC = 1600-1;		// count from 0 to 1599 => 16 000 000 / 1 600 = 10k

	// set auto reload value
	TIM2->ARR = 10000-1;	// 10k/10k = 1

	// ---set output compare toggle mode---
	// enable tim2 ch. 1 in compare mode
	TIM2->CCMR1 = OC_TOGGLE;

	// enable CC1E: capture/compare 1 output enable
	TIM2->CCER = CCER_CC1E;

	// clear counter
	TIM2->CNT = 0;

	// enable timer
	TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_input_capture(void)
{
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set pa6 mode to alt fcn, know its 12 and 13: 2 bits per pin
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER |= (1U << 13);

	// set pa6 alt fcn type to TIM3_CH1 (AF02)
	GPIOA->AFR[0] |= AFR6_TIM;

	// enable clock access to tim3
	RCC->APB1ENR |= TIM3EN;

	// set prescaler
	TIM3->PSC = 16000-1;

	// set ch1 to input capture at every edge CCMR1
	TIM3->CCMR1 = CCER_CCIS;

	// set ch1 to capture at rising edge (default state)
	TIM3->CCER = CCER_CC1E;

	// enable tim3
	TIM3->CR1 = CR1_CEN;
}























