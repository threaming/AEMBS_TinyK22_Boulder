/*
 * mySystemView.c
 *
 *  Created on: 29.03.2023
 *      Author: Ming
 */


#include "McuRTT.h"
#include "McuSystemView.h"

void myInterrupt(void){
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	McuSystemView_RecordEnterISR();
#endif
	/* ... */
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	McuSystemView_RecordExitISR();
#endif
}

void mySystemView_Test(void){
	McuSystemView_Print((const char*)"User pressed a key\r\n");
	McuSystemView_Warn((const char*)"Warning, a running Elefant\r\n");
	McuSystemView_Error((const char*)"Error, motivation not found\r\n");

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	McuSystemView_OnUserStart(1);	// using ID 1
#endif
	/* ... */
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	McuSystemView_OnUserStop(1);	// using ID 1
#endif
}

void mySystemView_Init(void){
	McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
	McuSystemView_Init();
	SEGGER_SYSVIEW_Start();	// start recording from beginning
#endif
}
