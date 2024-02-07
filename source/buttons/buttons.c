/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "buttons.h"
#include "buttons_config.h"
#include <assert.h>
#include "McuButton.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "leds.h"
#include "debounce.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_LPC
  #include "fsl_pint.h"
  #include "fsl_syscon.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

typedef struct BTN_Desc_t {
  McuBtn_Handle_t handle; /* handle of button pin */
} BTN_Desc_t;

static BTN_Desc_t BTN_Infos[BTN_NOF_BUTTONS];

BTN_Buttons_e BTN_RotateButton(BTN_Buttons_e button) {
#if BTN_CONFIG_ROTATION==0
  return button;
#elif BTN_CONFIG_ROTATION==180
  if (button == BTN_NAV_LEFT) {
    return BTN_NAV_RIGHT;
  } else if (button == BTN_NAV_RIGHT) {
    return BTN_NAV_LEFT;
  } else if (button == BTN_NAV_UP) {
    return BTN_NAV_DOWN;
  } else if (button == BTN_NAV_DOWN) {
    return BTN_NAV_UP;
  }
  return button;
#endif
}

bool BTN_IsPressed(BTN_Buttons_e btn) {
  assert(btn<BTN_NOF_BUTTONS);
  return McuBtn_IsOn(BTN_Infos[btn].handle);
}

uint32_t BTN_GetButtons(void) {
  uint32_t val = 0;

  if (BTN_IsPressed(BTN_NAV_UP)) {
    val |= BTN_BIT_NAV_UP;
  }
  if (BTN_IsPressed(BTN_NAV_DOWN)) {
    val |= BTN_BIT_NAV_DOWN;
  }
  if (BTN_IsPressed(BTN_NAV_LEFT)) {
    val |= BTN_BIT_NAV_LEFT;
  }
  if (BTN_IsPressed(BTN_NAV_RIGHT)) {
    val |= BTN_BIT_NAV_RIGHT;
  }
  if (BTN_IsPressed(BTN_NAV_CENTER)) {
    val |= BTN_BIT_NAV_CENTER;
  }
#if McuLib_CONFIG_CPU_IS_LPC
  if (BTN_IsPressed(BTN_USER)) {
    val |= BTN_BIT_USER;
  }
#endif
  return val;
}

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
/* IDs for SystemView */
#define MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT  (0)

static void SysViewLogStart(void) {
  McuSystemView_RecordEnterISR();
  McuSystemView_Print((const char*)"Pressed button\r\n");
  McuSystemView_OnUserStart(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
}
#endif

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
static void SysViewLogEnd(void) {
  McuSystemView_OnUserStop(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
  McuSystemView_RecordExitISR();
}
#endif

#if McuLib_CONFIG_CPU_IS_KINETIS
void PORTA_IRQHandler(void) {
  uint32_t flags;
  uint32_t buttons = 0;
  BaseType_t xHigherPriorityTaskWoken = false;

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SysViewLogStart();
#endif
  flags = GPIO_PortGetInterruptFlags(GPIOA);
  if (flags&(1U<<BUTTONS_PINS_NAVLEFT_PIN)) {
    buttons |= BTN_BIT_NAV_LEFT;
  }
  if (flags&(1U<<BUTTONS_PINS_NAVRIGHT_PIN)) {
    buttons |= BTN_BIT_NAV_RIGHT;
  }
  GPIO_PortClearInterruptFlags(GPIOA, flags);
  Debounce_StartDebounceFromISR(buttons, &xHigherPriorityTaskWoken);
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SysViewLogEnd();
#endif
  if (xHigherPriorityTaskWoken) {
    taskYIELD();
  }
  __DSB();
}
#endif

#if McuLib_CONFIG_CPU_IS_KINETIS
void PORTB_IRQHandler(void) {
  uint32_t flags;
  uint32_t buttons = 0;
  BaseType_t xHigherPriorityTaskWoken = false;

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SysViewLogStart();
#endif
  flags = GPIO_PortGetInterruptFlags(GPIOB);
  if (flags&(1U<<BUTTONS_PINS_NAVCENTER_PIN)) {
    buttons |= BTN_BIT_NAV_CENTER;
  }
  if (flags&(1U<<BUTTONS_PINS_NAVDOWN_PIN)) {
    buttons |= BTN_BIT_NAV_DOWN;
  }
  if (flags&(1U<<BUTTONS_PINS_NAVUP_PIN)) {
    buttons |= BTN_BIT_NAV_UP;
  }
  GPIO_PortClearInterruptFlags(GPIOB, flags);
  Debounce_StartDebounceFromISR(buttons, &xHigherPriorityTaskWoken);
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SysViewLogEnd();
#endif
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  __DSB(); /* need barrier due ARM Cortex bug */
}
#endif

#if McuLib_CONFIG_CPU_IS_LPC
static void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status) {
  BaseType_t xHigherPriorityTaskWoken = false;

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SysViewLogStart();
#endif
  switch(pintr) {
    case kPINT_PinInt0: Debounce_StartDebounceFromISR(BTN_BIT_USER, &xHigherPriorityTaskWoken); break;
    case kPINT_PinInt1: Debounce_StartDebounceFromISR(BTN_BIT_NAV_UP, &xHigherPriorityTaskWoken); break;
    case kPINT_PinInt2: Debounce_StartDebounceFromISR(BTN_BIT_NAV_DOWN, &xHigherPriorityTaskWoken); break;
    case kPINT_PinInt3: Debounce_StartDebounceFromISR(BTN_BIT_NAV_LEFT, &xHigherPriorityTaskWoken); break;
    case kPINT_PinInt4: Debounce_StartDebounceFromISR(BTN_BIT_NAV_RIGHT, &xHigherPriorityTaskWoken); break;
    case kPINT_PinInt5: Debounce_StartDebounceFromISR(BTN_BIT_NAV_CENTER, &xHigherPriorityTaskWoken); break;
    default:
      break;
  }
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SysViewLogEnd();
#endif
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
#endif

void BTN_Deinit(void) {
#if McuLib_CONFIG_CPU_IS_KINETIS
  DisableIRQ(PORTA_IRQn);
  DisableIRQ(PORTB_IRQn);
#endif
  for(int i=0; i<BTN_NOF_BUTTONS; i++) {
    BTN_Infos[i].handle = McuBtn_DeinitButton(BTN_Infos[i].handle);
  }
}

void BTN_Init(void) {
#if McuLib_CONFIG_CPU_IS_KINETIS
  McuBtn_Config_t btnConfig;

  BUTTONS_ENABLE_CLOCK();
  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.gpio = BUTTONS_PINS_NAVCENTER_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVCENTER_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVCENTER_PIN;
#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 /* V7 does not have hardware pull-ups on the board */
  btnConfig.hw.pull = McuGPIO_PULL_UP;
#endif
  BTN_Infos[BTN_NAV_CENTER].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVLEFT_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVLEFT_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVLEFT_PIN;
#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 /* V7 does not have hardware pull-ups on the board */
  btnConfig.hw.pull = McuGPIO_PULL_UP;
#endif
  BTN_Infos[BTN_NAV_LEFT].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVRIGHT_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVRIGHT_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVRIGHT_PIN;
#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 /* V7 does not have hardware pull-ups on the board */
  btnConfig.hw.pull = McuGPIO_PULL_UP;
#endif
  BTN_Infos[BTN_NAV_RIGHT].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVUP_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVUP_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVUP_PIN;
#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 /* V7 does not have hardware pull-ups on the board */
  btnConfig.hw.pull = McuGPIO_PULL_UP;
#endif
  BTN_Infos[BTN_NAV_UP].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVDOWN_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVDOWN_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVDOWN_PIN;
#if PL_CONFIG_BOARD_ID==PL_CONFIG_BOARD_ID_TINYK22_APROG_HAT_V7 /* V7 does not have hardware pull-ups on the board */
  btnConfig.hw.pull = McuGPIO_PULL_UP;
#endif
  BTN_Infos[BTN_NAV_DOWN].handle = McuBtn_InitButton(&btnConfig);

  PORT_SetPinInterruptConfig(BUTTONS_PINS_NAVLEFT_PORT,  BUTTONS_PINS_NAVLEFT_PIN,  kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_NAVRIGHT_PORT, BUTTONS_PINS_NAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  NVIC_SetPriority(PORTA_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTA_IRQn);

  PORT_SetPinInterruptConfig(BUTTONS_PINS_NAVDOWN_PORT, BUTTONS_PINS_NAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_NAVUP_PORT,   BUTTONS_PINS_NAVUP_PIN,   kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_NAVCENTER_PORT, BUTTONS_PINS_NAVCENTER_PIN, kPORT_InterruptFallingEdge);
  NVIC_SetPriority(PORTB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTB_IRQn);
#elif McuLib_CONFIG_CPU_IS_LPC
  /* user button on LPC845-BRK board: PIO0_4 */

  McuBtn_Config_t btnConfig;

  BUTTONS_ENABLE_CLOCK();
  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.gpio = BUTTONS_PINS_USER_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_USER_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_USER_PIN;
  btnConfig.hw.iocon = BUTTONS_PINS_USER_IOCON;
  BTN_Infos[BTN_USER].handle = McuBtn_InitButton(&btnConfig);
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, BUTTONS_PINS_USER_PINTSEL);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVUP_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVUP_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVUP_PIN;
  btnConfig.hw.iocon = BUTTONS_PINS_NAVUP_IOCON;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_UP].handle = McuBtn_InitButton(&btnConfig);
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt1, BUTTONS_PINS_NAVUP_PINTSEL);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVDOWN_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVDOWN_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVDOWN_PIN;
  btnConfig.hw.iocon = BUTTONS_PINS_NAVDOWN_IOCON;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_DOWN].handle = McuBtn_InitButton(&btnConfig);
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt2, BUTTONS_PINS_NAVDOWN_PINTSEL);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVLEFT_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVLEFT_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVLEFT_PIN;
  btnConfig.hw.iocon = BUTTONS_PINS_NAVLEFT_IOCON;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_LEFT].handle = McuBtn_InitButton(&btnConfig);
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt3, BUTTONS_PINS_NAVLEFT_PINTSEL);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVRIGHT_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVRIGHT_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVRIGHT_PIN;
  btnConfig.hw.iocon = BUTTONS_PINS_NAVRIGHT_IOCON;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_RIGHT].handle = McuBtn_InitButton(&btnConfig);
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt4, BUTTONS_PINS_NAVRIGHT_PINTSEL);

  btnConfig.hw.gpio = BUTTONS_PINS_NAVCENTER_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_NAVCENTER_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_NAVCENTER_PIN;
  btnConfig.hw.iocon = BUTTONS_PINS_NAVCENTER_IOCON;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_CENTER].handle = McuBtn_InitButton(&btnConfig);
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt5, BUTTONS_PINS_NAVCENTER_PINTSEL);

  PINT_Init(PINT); /* Initialize PINT */
  PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge, pint_intr_callback); /* Setup Pin Interrupt 0 for rising edge */
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0); /* Enable callbacks for PINT0 by Index */

  PINT_PinInterruptConfig(PINT, kPINT_PinInt1, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt1);

  PINT_PinInterruptConfig(PINT, kPINT_PinInt2, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt2);

  PINT_PinInterruptConfig(PINT, kPINT_PinInt3, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt3);

  PINT_PinInterruptConfig(PINT, kPINT_PinInt4, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt4);

  PINT_PinInterruptConfig(PINT, kPINT_PinInt5, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt5);

#endif
}
