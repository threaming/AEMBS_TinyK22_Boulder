/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef IMAGES_FACE_H_
#define IMAGES_FACE_H_

#include "McuGDisplaySSD1306.h"

/*!
 * \brief Return the image
 * \return Pointer to the (const) image data
 */
const PIMAGE Face_GetImage(void);

#endif /* IMAGES_FACE_H_ */
