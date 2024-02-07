/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    01_AEMBY_tinyK22.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK22F51212.h"
#include "fsl_debug_console.h"
#include "platform.h"

//static float f0 = 1.0f, f1 = 2.0f;
//static double d0 = 1.0, d1 = 2.0;

/*
 * @brief   Application entry point.
 */
int main(void) {
	PL_Init();
	vTaskStartScheduler();	// start RTOS

/* Measuring Cycles */
    //PRINTF("Hello World\n"); // 242255 Zyklen
//
//    f0 = f1*3.0f;	// 9 Zyklen
//    d0 = d1*3.0;	// 92 Zyklen

    /* Handles */
    //static McuGPIO_Handle_t myJoystick;
    //static McuGPIO_Handle_t myLED;

    /* Configure Pins for Joystick Push PTB16*/
//    McuGPIO_Config_t config;
//    McuGPIO_GetDefaultConfig(&config);
//    config.hw.gpio = GPIOB;
//    config.hw.port = PORTB;
//    config.hw.pin = 16;
//    config.isHighOnInit = true;
//    config.isInput = true;
//    config.hw.pull = McuGPIO_PULL_UP;
//    myJoystick = McuGPIO_InitGPIO(&config);
//    if(myJoystick == NULL){
//    	while(true){ /* error */ }
//    }

    /* create tasks and run scheduler */
    //MyTasks_Init();
    /* doesn't get here */

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
//        if(McuGPIO_GetValue(myJoystick)){
//        	LEDS_On(LEDS_RED);
//        }
//        else{
//        	LEDS_Off(LEDS_RED);
//        }
//        LEDS_Neg(LEDS_GREEN);
//        LEDS_Neg(LEDS_ORANGE);
//        McuWait_Waitms(250);
    }
    return 0 ;
}
