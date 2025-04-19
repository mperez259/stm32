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



#endif /* ADC_H_ */
