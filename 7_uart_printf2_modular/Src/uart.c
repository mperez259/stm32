#include "uart.h"

#define GPIOAEN				(1U << 0)
#define UART2EN				(1U << 17)

#define CR1_TE				(1U << 3)
#define CR1_UE				(1U << 13)
#define SR_TXE				(1U << 7)

#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ

#define UART_BAUDRATE		115200	// arbitrary


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(int ch);

int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void uar2_tx_inint(void) {

	// ******configure uart gpio pin********
	// enable clock access to gpiao
	RCC->AHB1ENR |= GPIOAEN;
	// set PA2 mode to alternate fnc mode
	GPIOA->MODER |= (1U << 5);
	GPIOA->MODER &=~ (1U << 4);
	// set pA2 AF type to UART_TX (AF7) AFR[] first index AFRL, second AFRLH
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	// ******configure uart module********
	// enable clock access to uart2
	RCC->APB1ENR |= UART2EN;
	// config uart baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	// configure transfer direction from UART_CR1 RefManual
	USART2->CR1 = CR1_TE; // note no OR operator, sets everyting else to 1, doesn't keep original registers val.
	// enable uart module
	USART2->CR1 |= CR1_UE;

}

void uart2_write(int ch) {

	// make sure transmit data reg is empty
	while(!(USART2->SR & SR_TXE)) {}
	// write to transmit data reg USART_SR status register bit 7
		USART2->DR = (ch & 0xFF);

}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate) {

	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);

}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate){
	return (PeriphClk + (BaudRate/2U)) / BaudRate;
}
