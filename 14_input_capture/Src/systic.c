#include "stm32f4xx.h"

#define SYSTIC_LOAD_VAL				16000 //16000 cycles per second
#define CTRL_ENABLE					(1U << 0)
#define CTRL_CLKSOURCE				(1U << 2)
#define CTRL_COUNTFLAG				(1U << 16)



void systicDelayMS(int n)
{

	// config systic (SysTick -> )
	// reload with number of clocks per millisecond
	SysTick->LOAD = SYSTIC_LOAD_VAL;

	// clear systic current value reg.
	SysTick->VAL = 0;

	// enable systick and internal clock
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSOURCE;

	for(int i = 0; i < n; i++) {
		// wait until countflag is set
		while(!(SysTick->CTRL & CTRL_COUNTFLAG)) {}
	}

	SysTick->CTRL = 0;

}
