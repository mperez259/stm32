/*
 * timer.h
 *
 *  Created on: Apr 17, 2025
 *      Author: m
 */

#ifndef TIMER_H_
#define TIMER_H_


void tim2_1hz_init(void);
void tim2_1hz_interrupt_init(void);



#define SR_UIF				(1U << 0)

#endif /* TIMER_H_ */
