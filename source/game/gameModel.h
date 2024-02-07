/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include <stdint.h>
#include <stdbool.h>
#include "game_config.h"
#include "McuGDisplaySSD1306.h"
#include "sprite.h"

typedef enum GameState_e {
  GAME_STATE_INTRO,
  GAME_STATE_RUNNING,
} GameState_e;

GameState_e Game_GetState(void);
void Game_SetState(GameState_e state);

void Game_ResetScore (void);
uint32_t Game_GetScore (void);
void Game_AddScore (uint32_t score);

bool Game_CheckCollisions(void);
bool Game_AgeAndCheckIfAlive(void);

#include "boulder.h"
void Game_CreateBoulderTileSprite(Boulder_Tile_e tile, int x, int y);
Sprite_t *Game_GetBoulderList(void);
Sprite_t *Game_GetDiamondList(void);
void Game_HandleFallingItems(void);
void Game_HandleMonsterMoving(void);

bool Game_CheckIfGameLost(void);
bool Game_CheckIfGameWon(void);

/*!
 * \brief Iterator to get all the sprite lists in the model (e.g. for painting)
 * \param cntr Iterator counter: Initialize with zero. Iterator will increase the value. If value returned is zero, list end has been reached.
 * \return Address of the List of Sprites, might be NULL
 */
Sprite_t **Game_IteratorGetSpriteLists(int *cntr);

typedef enum Game_Player_Speed_e {
  Game_Player_Speed_Normal,
  Game_Player_Speed_Fast,
  Game_Player_Speed_Fastest
} Game_Player_Speed_e;

typedef enum Game_PlayerAction_e {
  Game_Player_Move_Up,
  Game_Player_Move_Down,
  Game_Player_Move_Left,
  Game_Player_Move_Right,
} Game_PlayerAction_e;

/*!
 * \brief Perform a player action
 * \param action Action to be performed
 * \param speed Speed of action
 */
void Game_PlayerAction(Game_PlayerAction_e action, Game_Player_Speed_e speed);

/*!
 * \brief Free and release all game sprites
 */
void Game_FreeSprites(void);

/*!
 * \brief Create a new game and initialize model data structure.
 */
void Game_New(uint8_t gameLevel);

/*!
 * \brief Model module de-initialization.
 */
void Game_ModelDeinit(void);

/*!
 * \brief Model module initialization.
 */
void Game_ModelInit(void);

#endif /* GAMEMODEL_H_ */
