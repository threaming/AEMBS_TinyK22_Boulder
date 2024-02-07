/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "boom0.h"

static const uint8_t pixData[] = {
  0b00000000,
  0b10011001,
  0b01000010,
  0b10011001,
  0b01000010,
  0b10011001,
  0b00100100,
  0b00000000,
};

static const TIMAGE image = {
  .width =  8, /* .header.w */
  .height = 8, /* .header.h */
  .size = sizeof(pixData),
  .pixmap = pixData,
  .name = "boom0.bmp",
};

const PIMAGE Boom0_GetImage(void) {
  return (PIMAGE)&image;
}
