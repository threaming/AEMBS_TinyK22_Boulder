/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

#include "platform.h"

#define LEDS_CONFIG_HAS_RED_LED            (   PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_LPC845_BRK \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V3 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V4 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V5 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V6 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 \
                                            )

#define LEDS_CONFIG_HAS_GREEN_LED          (   PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_LPC845_BRK \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V3 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V4 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V5 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V6 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 \
                                            )

#define LEDS_CONFIG_HAS_BLUE_LED           (   PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_LPC845_BRK \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V3 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V4 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V5 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V6 \
                                            ) /* HAT V7 does not have a blue LED */

#define LEDS_CONFIG_HAS_ORANGE_LED         (   PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V3 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V4 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V5 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V6 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 \
                                            )

#define LEDS_CONFIG_HAS_BLUE_TINY_LED      (   PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V3 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V4 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V5 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V6 \
                                            || PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 \
                                            )

#if McuLib_CONFIG_CPU_IS_KINETIS
  /* blue LED on tinyK22 plus LEDs on HAT */
  #define LEDS_CONFIG_ENABLE_CLOCK()     CLOCK_EnableClock(kCLOCK_PortC) /* enable clocking for port used by LEDs */

#if LEDS_CONFIG_HAS_RED_LED
  #define LEDS_CONFIG_RED_GPIO          GPIOC
  #define LEDS_CONFIG_RED_PORT          PORTC
  #define LEDS_CONFIG_RED_PIN           11U
  #define LEDS_CONFIG_RED_LOW_ACTIVE    false
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  #define LEDS_CONFIG_GREEN_GPIO        GPIOC
  #define LEDS_CONFIG_GREEN_PORT        PORTC
  #define LEDS_CONFIG_GREEN_PIN         9U
  #define LEDS_CONFIG_GREEN_LOW_ACTIVE  false
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  #define LEDS_CONFIG_BLUE_GPIO         GPIOC
  #define LEDS_CONFIG_BLUE_PORT         PORTC
  #define LEDS_CONFIG_BLUE_PIN          8U
  #define LEDS_CONFIG_BLUE_LOW_ACTIVE   false
#endif


#if LEDS_CONFIG_HAS_ORANGE_LED
  #define LEDS_CONFIG_ORANGE_GPIO       GPIOC
  #define LEDS_CONFIG_ORANGE_PORT       PORTC
  #define LEDS_CONFIG_ORANGE_PIN        10U
  #define LEDS_CONFIG_ORANGE_LOW_ACTIVE false
#endif

#if LEDS_CONFIG_HAS_BLUE_TINY_LED
  #define LEDS_CONFIG_BLUE_TINY_GPIO        GPIOC
  #define LEDS_CONFIG_BLUE_TINY_PORT        PORTC
  #define LEDS_CONFIG_BLUE_TINY_PIN         2U
  #define LEDS_CONFIG_BLUE_TINY_LOW_ACTIVE  true
#endif

#elif McuLib_CONFIG_CPU_IS_LPC
   /* Green: PIO1_0
    * Blue:  PIO1_1
    * Red:   PIO1_2 */
  #define LEDS_CONFIG_ENABLE_CLOCK()    GPIO_PortInit(GPIO, 1) /* ungate the clocks for GPIO1: used for LED */

#if LEDS_CONFIG_HAS_RED_LED
  #define LEDS_CONFIG_RED_GPIO          GPIO
  #define LEDS_CONFIG_RED_PORT          1
  #define LEDS_CONFIG_RED_PIN           2
  #define LEDS_CONFIG_RED_IOCON         IOCON_INDEX_PIO1_2
  #define LEDS_CONFIG_RED_LOW_ACTIVE    true
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  #define LEDS_CONFIG_GREEN_GPIO        GPIO
  #define LEDS_CONFIG_GREEN_PORT        1
  #define LEDS_CONFIG_GREEN_PIN         0
  #define LEDS_CONFIG_GREEN_IOCON       IOCON_INDEX_PIO1_0
  #define LEDS_CONFIG_GREEN_LOW_ACTIVE  true
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  #define LEDS_CONFIG_BLUE_GPIO         GPIO
  #define LEDS_CONFIG_BLUE_PORT         1
  #define LEDS_CONFIG_BLUE_PIN          1
  #define LEDS_CONFIG_BLUE_IOCON        IOCON_INDEX_PIO1_1
  #define LEDS_CONFIG_BLUE_LOW_ACTIVE   true
#endif

#endif

#endif /* LEDS_CONFIG_H_ */
