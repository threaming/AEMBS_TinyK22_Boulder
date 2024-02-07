/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BOULDER_IMAGES_H_
#define BOULDER_IMAGES_H_

#include "McuGDisplaySSD1306.h"

/*!
 * \brief Return the images for the game (main image and possible second animation image
 * \return Pointer to the (const) image data
 */
const PIMAGE BoulderImages_GetPlayer(void);
const PIMAGE BoulderImages_GetPlayerAnim0(void);

const PIMAGE BoulderImages_GetMonster(void);
const PIMAGE BoulderImages_GetMonsterAnim0(void);

const PIMAGE BoulderImages_GetDirt(void);

const PIMAGE BoulderImages_GetDiamond(void);
const PIMAGE BoulderImages_GetDiamondAnim0(void);
const PIMAGE BoulderImages_GetDiamondAnim1(void);

const PIMAGE BoulderImages_GetBoulder(void);

const PIMAGE BoulderImages_GetWall(void);

#endif /* BOULDER_IMAGES_H_ */
