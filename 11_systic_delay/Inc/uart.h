/*
 * uart.h
 *
 *  Created on: Apr 15, 2025
 *      Author: m
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include <stdint.h>

void uart2_tx_inint(void);
char uart2_read(void);
void uart2_rxtx_inint(void);
void uart2_write(int);

#endif /* UART_H_ */
