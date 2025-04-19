// using TIM2 for this one -> APB1 bus

#include "stm32f4xx.h"


#define TIM2EN		(1U << 0)
#define CR1_CEN		(1U << 0)
#define DIER_UEI	(1U << 0)


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

void tim2_1hz_interrupt_init(void)
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

	// enable TIM int
	TIM2->DIER |= DIER_UEI;

	// enable interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);

}

