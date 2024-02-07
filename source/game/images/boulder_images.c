/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "game/images/boulder_images.h"

static const uint8_t pixDataPlayer[] = {
	0x78,
	0x48,
	0x30,
	0xb4,
	0x78,
	0x30,
	0x48,
};

static const TIMAGE player = {
  .width = 6,
  .height = 7,
  .size = 8,
  .pixmap = pixDataPlayer,
  .name = "player",
};

static const uint8_t pixDataPlayerAnim0[] = {
	0x78,
	0x48,
	0x30,
	0x78,
	0xb4,
	0x30,
	0x48,
};

static const TIMAGE playerAnim0 = {
  .width = 6,
  .height = 7,
  .size = 8,
  .pixmap = pixDataPlayerAnim0,
  .name = "playerAnim0",
};

static const uint8_t pixDataDirt[] = {
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
};

static const TIMAGE dirt = {
  .width = 8,
  .height = 8,
  .size = 8,
  .pixmap = pixDataDirt,
  .name = "dirt",
};

static const uint8_t pixDataDiamond[] = {
  0b00000000,
  0b00000000,
  0b00111100,
  0b11111111,
  0b10100101,
  0b01111110,
  0b00111100,
  0b00011000,
};

static const TIMAGE diamond = {
  .width = 8,
  .height = 8,
  .size = 8,
  .pixmap = pixDataDiamond,
  .name = "diamond",
};

static const uint8_t pixDataDiamondAnim0[] = {
  0b10000001,
  0b01000010,
  0b00111000,
  0b01000010,
  0b01000010,
  0b10000001,
};

static const TIMAGE diamondAnim0 = {
  .width = 8,
  .height = 6,
  .size = 8,
  .pixmap = pixDataDiamondAnim0,
  .name = "diamondAnim0",
};

static const uint8_t pixDataDiamondAnim1[] = {
  0b01000010,
  0b00111000,
  0b01000010,
  0b01000010,
  0b10000001,
};

static const TIMAGE diamondAnim1 = {
  .width = 8,
  .height = 5,
  .size = 8,
  .pixmap = pixDataDiamondAnim1,
  .name = "diamondAnim1",
};

static const uint8_t pixDataBoulder[] = {
  0b00000000,
  0b00111000,
  0b01111100,
  0b11111110,
  0b11111111,
  0b01111110,
  0b01111110,
  0b00111100,
};

static const TIMAGE boulder = {
  .width = 8,
  .height = 8,
  .size = 8,
  .pixmap = pixDataBoulder,
  .name = "boulder",
};

static const uint8_t pixDataWall[] = {
  0xff,
  0xff,
  0xff,
  0xff,
  0xff,
  0xff,
  0xff,
  0xff,
};

static const TIMAGE wall = {
  .width = 8,
  .height = 8,
  .size = 8,
  .pixmap = pixDataWall,
  .name = "wall",
};

static const uint8_t pixDataMonster[] = {
  0b01000010,
  0b00111110,
  0b01111110,
  0b11011011,
  0b01100110,
  0b10100101,
  0b10000001,
};

static const TIMAGE monster = {
  .width = 8,
  .height = 7,
  .size = 8,
  .pixmap = pixDataMonster,
  .name = "monster",
};

static const uint8_t pixDataMonsterAnim0[] = {
  0b00100100,
  0b00111110,
  0b01111110,
  0b11011011,
  0b01111110,
  0b10111101,
  0b01000010,
};

static const TIMAGE monsterAnim0 = {
  .width = 8,
  .height = 7,
  .size = 8,
  .pixmap = pixDataMonsterAnim0,
  .name = "monster0",
};

const PIMAGE BoulderImages_GetPlayer(void) {
  return (PIMAGE)&player;
}

const PIMAGE BoulderImages_GetPlayerAnim0(void) {
  return (PIMAGE)&playerAnim0;
}

const PIMAGE BoulderImages_GetDirt(void) {
  return (PIMAGE)&dirt;
}

const PIMAGE BoulderImages_GetMonster(void) {
  return (PIMAGE)&monster;
}

const PIMAGE BoulderImages_GetMonsterAnim0(void) {
  return (PIMAGE)&monsterAnim0;
}

const PIMAGE BoulderImages_GetDiamond(void) {
  return (PIMAGE)&diamond;
}

const PIMAGE BoulderImages_GetDiamondAnim0(void) {
  return (PIMAGE)&diamondAnim0;
}

const PIMAGE BoulderImages_GetDiamondAnim1(void) {
  return (PIMAGE)&diamondAnim1;
}

const PIMAGE BoulderImages_GetBoulder(void) {
  return (PIMAGE)&boulder;
}

const PIMAGE BoulderImages_GetWall(void) {
  return (PIMAGE)&wall;
}
