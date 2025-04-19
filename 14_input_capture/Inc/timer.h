/*
 * timer.h
 *
 *  Created on: Apr 17, 2025
 *      Author: m
 */

#ifndef TIMER_H_
#define TIMER_H_


void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);

#define SR_CC1IF			(1U << 1)
#define SR_UIF				(1U << 0)

#endif /* TIMER_H_ */
