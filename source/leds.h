/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MY_LEDS_H_
#define MY_LEDS_H_

#include "McuLib.h"
#include "leds_config.h"
#include <stdint.h>
#include <stdbool.h>

/*!
 * handles for the different LEDs
 */
typedef enum LEDS_Leds_e {
#if LEDS_CONFIG_HAS_RED_LED
  LEDS_RED,      /*!< LEDS_RED */
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  LEDS_GREEN,    /*!< LEDS_GREEN */
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  LEDS_BLUE,     /*!< LEDS_BLUE */
#endif
#if LEDS_CONFIG_HAS_ORANGE_LED
  LEDS_ORANGE,   /*!< LEDS_ORANGE */
#endif
#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  LEDS_TINY_BLUE,/*!< LEDS_TINY_BLUE */
#endif
} LEDS_Leds_e;

/*!
 * \brief Turn LED on
 * \param led LED handle
 */
void LEDS_On(LEDS_Leds_e led);

/*!
 * \brief Turn LED off
 * \param led LED handle
 */
void LEDS_Off(LEDS_Leds_e led);

/*!
 * \brief Toggle LED
 * \param led LED handle
 */
void LEDS_Neg(LEDS_Leds_e led);

/*!
 * \brief Module initialization, call it to initialize the driver
 */
void LEDS_Init(void);

/*!
 * \brief Module de-initialization, call it to de-initialize the driver
 */
void LEDS_Deinit(void);

#endif /* MY_LEDS_H_ */
