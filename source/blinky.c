/*
 * blinky.c
 *
 *  Created on: 21.02.2023
 *      Author: Ming
 */


#include "blinky.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "pin_mux.h"


void delay(void) {
	uint32_t i;

	for(i=0;i<500000;i++) {
		__asm volatile ("nop");
	}
}

void Blinky_Run(void){
	while(1){
		delay();
		GPIO_PortToggle(BOARD_INITPINS_LED_BLUE_GPIO, BOARD_INITPINS_LED_BLUE_GPIO_PIN_MASK);
	}
}
