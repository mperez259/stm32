/*
 * exti.h
 *
 *  Created on: Apr 17, 2025
 *      Author: m
 */

#ifndef EXTI_H_
#define EXTI_H_


#include "stm32f4xx.h"

void pc13_exti_init(void);

#define LINE13		(1U << 13) // for exti pending register, to know when int occured

#endif /* EXTI_H_ */
