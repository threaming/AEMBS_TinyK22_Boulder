/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "hat/sensor.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "semphr.h"
#include "portmacro.h"
#if PL_CONFIG_USE_PARTIAL_UPDATE
  #include "game/gameView.h"
#endif

// only use one, depending on board used:
#include "McuSHT40.h"
//  #include "McuSHT31.h"

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

/* Global variable for values */
static float t, h;
/* Mutex for protecting the I2C bus */
static SemaphoreHandle_t i2cMutex = NULL;

/*
 * Task which takes the temperature and humidity from SHT40 every second
 * over the I2C-bus
 */
static void sensorTask(void *pv) {
  uint8_t res;
  uint8_t buf[32];

  for(;;) {
	if(sLock()){
		// use the one matching your sensor on the board:
		res = McuSHT40_ReadTempHum(&t, &h);
		//res = McuSHT31_ReadTempHum(&t, &h);
		sUnlock();
	}
	#if PL_CONFIG_USE_PARTIAL_UPDATE
		PaintBottomBar(t, h);
	#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS /* example printing sensor values with SystemView */
    McuUtility_strcpy(buf,  sizeof(buf), (unsigned char*)"res: ");
    McuUtility_strcatNum8u(buf, sizeof(buf), res);
    McuUtility_strcat(buf,  sizeof(buf), (unsigned char*)", t: ");
    McuUtility_strcatNumFloat(buf, sizeof(buf), t, 1);
    McuUtility_strcat(buf,  sizeof(buf), (unsigned char*)"C, h: ");
    McuUtility_strcatNumFloat(buf, sizeof(buf), h, 1);
    McuUtility_strcat(buf,  sizeof(buf), (unsigned char*)"%");
    McuSystemView_Print((char*)buf);
#endif
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

/*
 * Get temperature which is at most a second old
 */
void GetTemp(float *temp){
	*temp = t;
}

/*
 * Get humidity which is at most a second old
 */
void GetHum(float *hum){
	*hum = h;
}

/*
 * \brief Take mutex for a save I2C operation
 * \error timeout for 50ms, pdFALSE of mutex couldn't be taken
 */
BaseType_t sLock(void){
	if(xSemaphoreTakeRecursive(i2cMutex, pdMS_TO_TICKS(100))!= pdTRUE){ /* Error */
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_Error((const char*)"failed to take i2c mutex, deadlock?\r\n");
#endif
		return pdFALSE;
	}
	return pdTRUE;
}

/*
 * \brief Give mutex for a save I2C operation
 */
BaseType_t sUnlock(void){
	if(xSemaphoreGiveRecursive(i2cMutex) != pdTRUE){ /* Error */
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_Error((const char*)"failed to give i2c mutex, not the holder?\r\n");
#endif
		return pdFALSE;
	}
	return pdTRUE;
}

void Sensor_Deinit(void) {
	vSemaphoreDelete(i2cMutex);
}

void Sensor_Init(void) {
  BaseType_t res;
  i2cMutex = xSemaphoreCreateRecursiveMutex();
  if(!i2cMutex){	/* Error */
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	  McuSystemView_Error((const char*)"failed to create i2c mutex, stack full?\r\n");
#endif
	  while(1);
  }
  vQueueAddToRegistry ( i2cMutex , "i2c Mutex " );

  res = xTaskCreate(sensorTask, "sensor", 800/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL);
  if (res!=pdPASS) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	  McuSystemView_Error((const char*)"failed to create sensor task\r\n");
#endif
	  while(1);
  }
}
