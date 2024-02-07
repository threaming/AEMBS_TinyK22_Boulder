/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "McuLib.h"

#if defined(CPU_LPC845M301JBD48)
  #define PL_CONFIG_IS_LPC  (1)
  #define PL_CONFIG_IS_TINY (0)
#elif defined(CPU_MK22FN512VLH12)
  #define PL_CONFIG_IS_LPC  (0)
  #define PL_CONFIG_IS_TINY (1)
#else
  #error "unknown MCU?"
#endif

#define PL_CONFIG_BOARD_ID_LPC845_BRK            (1)
#define PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V3  (2) /* not supported yet, need to use I2C bit banging */
#define PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V4  (3)
#define PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V5  (4)
#define PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V6  (5)
#define PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7  (6)

#if McuLib_CONFIG_CPU_IS_LPC
  #define PL_CONFIG_BOARD_ID          PL_CONFIG_BOARD_ID_LPC845_BRK
#else
  #define PL_CONFIG_BOARD_ID          PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7
#endif

#define PL_CONFIG_USE_PARTIAL_UPDATE  (0)

/*!
 * \brief de-initializes the platform
 */
void PL_Deinit(void);

/*!
 * \brief initializes the platform
 */
void PL_Init(void);

#endif /* PLATFORM_H_ */
