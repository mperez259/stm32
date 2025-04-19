// where is the LED connected
// port: A
// pin: 5 (pin 21)
// address range GPIOA 0x4002 0000 - 0x4002 03FF

#define PERIPH_BASE 		(0x40000000UL) // UL => unsigned long
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET		(0x0000UL)
#define GPIOA_BASE 			(AHB1PERIPH_BASE + GPIOA_OFFSET)

// address peripherals start at ox4000 0000 => PERIPH_BASE
// add offset to get to the address you want. In this case
// use we want first address of GPIOA 0x4002 0000
// so offset will be 0x0002 0000

// RCC = Reset clock control => starting address (0x4200 38000)
#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

// in the documentation, there's Address offset: 0x30, basically add it to RCC_BASE
#define AHB1ENR_OFFSET		(0x00000030UL)
// need to type cast volatile unsigned int for registers, then dereference the array
// because it's writing into an address
#define MODE_R_OFFSET		(0x00UL)
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1ENR_OFFSET))

#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14UL)
#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

// enable GPIOA => change bit 0 OF RCC_AHB1ENR to 1
#define GPIOAEN				(1U << 0) // 0000 0000 0000 0000 0000 0000 0000 0000
									  // shift 1 at position 0 (1U << 0)
									  // 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5				(1U << 5)
#define LED_PIN				PIN5


/*
  (1U << 10) 	// set bit 10 to 1
  &=~(1U << 11) 	// set bit 11 and only 11 to 0
*/


int main(void) {

	/* 1. enable clock access to GPIOA*/
	RCC_AHB1EN_R |= GPIOAEN;

	/* 2. set PA5 as output pin */
	GPIOA_MODE_R |= (1U << 10); 	// only set bit 10 to 1 with OR operator |
	GPIOA_MODE_R &=~  (1U << 11); 	// set bit 11 and only 11 to 0;

	while(1) {
		// 3. set PA5 high
		//GPIOA_OD_R |= LED_PIN;

		// 4. Experiment: toggle PA5
		GPIOA_OD_R ^= LED_PIN;
		// add some delay
		for(int i = 0; i < 100000; i++) {}
	}
}

