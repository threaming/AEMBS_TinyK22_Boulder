/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "face.h" /* include of own header file */

/* Use https://lvgl.io/tools/imageconverter */

/* the bitmap data, copy from generated file */
static const uint8_t pixData[] = {
  /* put bitmap data here */
    0xff, 0xc0,
    0x80, 0x40,
    0xa1, 0x40,
    0x8c, 0x40,
    0x8c, 0x40,
    0x8c, 0x40,
    0xa1, 0x40,
    0xbf, 0x40,
    0x80, 0x40,
    0xff, 0xc0,
};

static const TIMAGE image = {
  .width = 10, /* number from converted file: .header.w */
  .height = 10, /* number from converted file: .header.h */
  .size = sizeof(pixData), /* size of bitmap data */
  .pixmap = pixData, /* pointer to bitmap data above */
  .name = "face.bmp", /* optional name of file */
};

const PIMAGE Face_GetImage(void) {
  return (PIMAGE)&image;
}

