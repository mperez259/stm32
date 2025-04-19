/*
 * adc.h
 *
 *  Created on: Apr 15, 2025
 *      Author: m
 */

#ifndef ADC_H_
#define ADC_H_


#include <stdint.h>
#include "stm32f4xx.h"

void PA1_ADC_INIT(void);
void start_conversion(void);
uint32_t adc_read(void);
void pa1_adc_interrupt_init(void);


#define EOC		(1U << 1)

#endif /* ADC_H_ */
