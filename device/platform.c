/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "math.h"
#include "blinky.h"
#include "cycles.h"
#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuButton.h"
#include "McuDebounce.h"
#include "McuGenericI2C.h"
#include "McuSHT40.h"
#include "McuGFont.h"
#include "leds.h"
#include "myTasks.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	#include "mySystemView.h"
#endif
#include "buttons/buttons.h"
#include "buttons/debounce.h"
#include "game/game.h"
#include "hat/sensor.h"

/* Some faster Stuff */
#define McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US          (0)
#define McuSSD1306_CONFIG_DYNAMIC_DISPLAY_ORIENTATION   (0)
#define McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION      McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE

#define McuGenericI2C_CONFIG_USE_MUTEX                  (0)

void PL_Init(void) {
	//Cycles_Init(); /* initialize cylce counter */
	//Blinky_Init();
	McuLib_Init();
	McuWait_Init();
	McuGPIO_Init();
	McuRTOS_Init();
	McuBtn_Init();
	McuDbnc_Init();
	McuGFont_Init();
	McuGenericI2C_Init();	// generic I2C module
	CLOCK_EnableClock(kCLOCK_PortB);	// I2C pins on Port B, needed for ResetBus()
	McuI2cLib_Init();		// I2C Library
	McuSHT40_Init();		// for ussage on HAT v7
	LEDS_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	mySystemView_Init();
#endif
	BTN_Init();
	Debounce_Init();
	MyTasks_Init();
	Game_Init();
//	Sensor_Init();	// done in game.c
}

void PL_Deinit(void) {
	Sensor_Deinit();
	Game_Deinit();
	Debounce_Deinit();
	BTN_Deinit();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	mySystemView_Init();
#endif
	LEDS_Deinit();
	McuGFont_Deinit();
	McuDbnc_Deinit();
	McuBtn_Deinit();
	McuRTOS_Deinit();
	McuGPIO_Deinit();
	McuWait_Deinit();
	McuLib_Deinit();
	//Cycles_Deinit();
}
