/*
 * myTasks.c
 *
 *  Created on: 17.03.2023
 *      Author: Ming
 */

#include "myTasks.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include <stdint.h>
#include <stdio.h>
#include "leds.h"
#include "mySystemView.h"
#include "McuSystemView.h"

//static uint32_t taskParam1 = 5;
static uint32_t taskParam2 = 502;
//static TaskHandle_t myTaskHndl = NULL;
static TaskHandle_t suicideHndl = NULL;
static TaskHandle_t blinkyHndl = NULL;

static void BlinkyTask (void *pvParameters){
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(true){
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_OnUserStart(1);
#endif
        LEDS_Neg(LEDS_TINY_BLUE);
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
        McuSystemView_OnUserStop(1);
#endif
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(20)); // For really periodic blinking
	}
}

static void mySuicide(void *pv) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	printf("hello, might kill myself later\n");
	vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10000));	// Wait 10s
	printf("Stop this light!\n");
	vTaskSuspend(blinkyHndl);
	vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10000));	// Wait 10s
	printf("Okay Okay, you can blink\n");
	vTaskResume(blinkyHndl);
	printf("byebye\n");
	vTaskDelete(NULL);			// suicide, NULL: Self referencing
	//vTaskDelete(suicideHndl);	// last call of this task
	/* never be reached */
}

//static void myTask(void *pv) {
//	uint32_t param = *(uint32_t*)pv;
//	printf("myTask param is %d\n", param);
//	mySystemView_Test();
//	while(true){
//		taskDISABLE_INTERRUPTS();	// no interrupts from now on
//		__asm("nop");
//		taskENABLE_INTERRUPTS();	// interrupts resume
//	}
//}

void MyTasks_Init(void){
	BaseType_t res;

	res = xTaskCreate(
		BlinkyTask, /*Task Code */
		"BlinkyWinky", /* Task name */
		400/sizeof(StackType_t), /* Stack size: 400 bytes protable*/
		NULL, /* Parameters: Global object! */
		tskIDLE_PRIORITY+2, /* Priority: medium-> tskIDLE_PRIORITY = 0 */
		&blinkyHndl); /* Task Handle */

	/* Fehlerbehandlung */
		if ( res!=pdPASS) {
			printf("ERROR Task Creation");
			while(true);
		}

	res = xTaskCreate(
		mySuicide, /*Task Code */
		"SuicideSquad", /* Task name */
		400/sizeof(StackType_t), /* Stack size: 400 bytes protable*/
		&taskParam2, /* Parameters: Global object! */
		tskIDLE_PRIORITY+1, /* Priority: lowest-> tskIDLE_PRIORITY = 0 */
		&suicideHndl); /* Task Handle */

	/* Fehlerbehandlung */
	if ( res!=pdPASS) {
		printf("ERROR Task Creation");
		while(true);
	}

	// vTaskStartScheduler();	// start RTOS // done on toplevel


	/* Graveyard RIP */

//	res = xTaskCreate(
//		myTask, /*Task Code */
//		"myTask1", /* Task name */
//		400/sizeof(StackType_t), /* Stack size: 400 bytes protable*/
//		&taskParam1, /* Parameters: Global object! */
//		tskIDLE_PRIORITY+1, /* Priority: lowest-> tskIDLE_PRIORITY = 0 */
//		&myTaskHndl); /* Task Handle */
//
//	/* Fehlerbehandlung */
//		if ( res!=pdPASS) {
//			printf("ERROR Task Creation");
//			while(true);
//		}
//
//	res = xTaskCreate(
//		myTask, /*Task Code */
//		"myTask2", /* Task name */
//		400/sizeof(StackType_t), /* Stack size: 400 bytes protable*/
//		&taskParam2, /* Parameters: Global object! */
//		tskIDLE_PRIORITY+1, /* Priority: lowest-> tskIDLE_PRIORITY = 0 */
//		NULL); /* Task Handle */
//
//	/* Fehlerbehandlung */
//		if ( res!=pdPASS) {
//			printf("ERROR Task Creation");
//			while(true);
//		}


	/* doesn't get here */
}
