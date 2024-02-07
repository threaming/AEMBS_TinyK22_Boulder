/*
 * csem.c
 *
 *  Created on: 26.06.2023
 *      Author: Ming
 */

#include "csem.h"
#include "semphr.h"
#include "queue.h"
#include "mySystemView.h"
#include "McuSystemView.h"
#include "McuRTOS.h"
#include "McuUtility.h"

SemaphoreHandle_t csem_hndl = NULL;

void Csem_Init(void){
	csem_hndl = xSemaphoreCreateCounting(NUM_OF_TOKENS, NUM_OF_INIT_TOKENS);
	if (csem_hndl == NULL) {	// Error!
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_Error((const char*)"failed to create semaphore, memory full?\r\n");
#endif
		for(;;) {}
	}
	vQueueAddToRegistry(csem_hndl, "MEP_CntSemaphore");

	/* Create Boss Task */
	res = xTaskCreate(
			BossTask,
			"BossTask",
			800/sizeof(StackType_t),
			NULL,
			tskIDLE_PRIORITY+2, // Priority: high
			NULL);
	if (res!=pdPASS) {	// Error detection
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_Error((const char*)"failed to create task, memory full?\r\n");
#endif
		for(;;) {}
	  }
}

void Csem_Deinit(void){
	vQueueUnregisterQueue(csem_hndl);
	vQueueDelete(csem_hndl);
}

static void BossTask (void *pvParameters){

	while (true){
		xSemaphoreTake(csem_hndl, portMAX_DELAY);
		/* Create Worker Task */
			res = xTaskCreate(
				WorkerTask,
				"workerTask",
				800/sizeof(StackType_t),
				NULL,
				tskIDLE_PRIORITY+1, // Priority: medium
				NULL);
			if (res!=pdPASS) {	// Error detection
		#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
				McuSystemView_Error((const char*)"failed to create task, memory full?\r\n");
		#endif
				for(;;) {}
			  }
	}
}

static void WorkerTask (void *pvParameters){
	int32_t r;
	r = McuUtility_random(0, 5000); /* random suicide time*/
	vTaskDelay(pdMS_TO_TICKS(r));
	xSemaphoreGive(csem_hndl);		// allow other worker
	vTaskDelete(NULL);				// suicide
}
