/*
 * Copyright (c) 2016-2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option
Instructions:
 - Remove the 'Template_' from the name and place this file into your 'src' folder.
 - Include it with the -include compiler option with:  "${ProjDirPath}/source/IncludeMcuLibConfig.h"
 - Add the following to the -I compiler option:
../McuLib
../McuLib/config
../McuLib/config/fonts
../McuLib/fonts
../McuLib/src
../McuLib/FreeRTOS/Source/include
../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuLib/SEGGER_RTT
../McuLib/SEGGER_Sysview
../McuLib/TraceRecorder
../McuLib/TraceRecorder/config
../McuLib/TraceRecorder/include
../McuLib/TraceRecorder/streamports/Jlink_RTT/include
../McuLib/HD44780
../McuLib/FatFS
../McuLib/FatFS/source

if using a CDT Build variable pointing to the library, the following can be used instead:
${MCULIB}
${MCULIB}/config
${MCULIB}/config/fonts
${MCULIB}/fonts
${MCULIB}/src
${MCULIB}/FreeRTOS/Source/include
${MCULIB}/FreeRTOS/Source/portable/GCC/ARM_CM4F
${MCULIB}/SEGGER_RTT
${MCULIB}/SEGGER_Sysview
${MCULIB}/TraceRecorder
${MCULIB}/TraceRecorder/config
${MCULIB}/TraceRecorder/include
${MCULIB}/TraceRecorder/streamports/Jlink_RTT/include
${MCULIB}/HD44780
${MCULIB}/minIni
${MCULIB}/FatFS
${MCULIB}/FatFS/source
 */

/* For ESP32 targets:
  - place the IncludeMcuLibConfig.h into the project 'config' folder
  - copy the template file McuLib\ESP32_CMakeLists.txt and rename it to McuLib\CMakeLists.text
  - add the following to your main CMakeLists.txt, between cmake_minimum_required() and the include():
list(APPEND EXTRA_COMPONENT_DIRS "../McuLib")
  - add the following after the include():
add_compile_options(-I../config)
add_compile_options(-include "../config/IncludeMcuLibConfig.h")

  - It should look similar to this:
    cmake_minimum_required(VERSION 3.5)

    list(APPEND EXTRA_COMPONENT_DIRS "../McuLib")

    include($ENV{IDF_PATH}/tools/cmake/project.cmake)

    add_compile_options(-I../config)
    add_compile_options(-include "../config/IncludeMcuLibConfig.h")

    project(idf-eclipse)

 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       (McuLib_CONFIG_CPU_VARIANT_NXP_LPC845) /* for LPC need to specify the actual device */
#elif 0 /* example configuration for LPC55xx */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       (McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69) /* for LPC need to specify the actual device */
#elif 1 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* ESP32 */
  #define McuLib_CONFIG_CPU_IS_ARM_CORTEX_M   (0)  /* ESP32 is detected automatically */
  #define configHEAP_SCHEME_IDENTIFICATION    (0)  /* ESP-IDF RTOS used */
  #define McuCriticalSection_CONFIG_USE_RTOS_CRITICAL_SECTION  (1) /* no native Extensa implementation yet */
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (1)
#define configTOTAL_HEAP_SIZE                (24*1024)
/* #define configUSE_HEAP_SECTION_NAME          (1) */
/* #define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS" */
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS             (0)

/* ----------------- Used Modules ----------------------*/
#define McuLib_CONFIG_MCUI2CLIB_ENABLED (1)		// enable McuI2cLib
#define MCUI2CLIB_CONFIG_USE_PORTB_B0_B1 (1)	// using I2C on B0/B1
#define I2C_RETRY_TIMES		(5000)				// set retry count for SDK

/*------------------ McuGenericI2C ---------------------*/
#define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE "McuI2cLib.h"	// header file to be used
#define McuGenericI2C_CONFIG_RECV_BLOCK McuI2cLib_RecvBlock			// callback to receive a block
#define McuGenericI2C_CONFIG_SEND_BLOCK McuI2cLib_SendBlock			// callback to send a block
#if McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START
	#define McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE McuI2cLib_SendBlockContinue // only used if we need to send a STOP without a START, needed for dome sensors
#endif
#define McuGenericI2C_CONFIG_SEND_STOP McuI2cLib_SendStop 			// callback to send a stop condition
#define McuGenericI2C_CONFIG_SELECT_SLAVE McuI2cLib_SelectSlave 	// callback to select a slave address
#define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE (0) 		// enable if a custom receive block callback shall be defined
#define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM McuI2cLib_RecvBlockCustom // custom receive block callback

/*------------------ OLED Driver -----------------------*/
#define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE	(1106)	// use SH1106
#define McuGDisplaySSD1306_CONFIG_CLEAR_DISPLAY_IN_INIT (1)

#endif /* INCLUDEMCULIBCONFIG_H_ */
