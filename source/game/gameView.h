/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "platform.h"
#include "game_config.h"

typedef enum Game_Screen_e {
  GAME_SCREEN_AEMBS,  /* show screen with module name */
  GAME_SCREEN_GRAPHICS, /*! \todo */
  GAME_SCREEN_TEMPERATURE, /*! \todo */
  GAME_SCREEN_GAMEPLAY, /* update gameplay screen and show all elements */
  GAME_SCREEN_WON,			// winner winner chicken dinner
  GAME_SCREEN_WON_SCORE,	// winner with scores
  GAME_SCREEN_LOST,			// Lost the game
  GAME_SCREEN_LOST_SCORE,	// Lost with score
  GAME_SCREEN_SCORE			// MEP: Just score
  /*! \todo add more items as needed */
} Game_Screen_e;

/*!
 * \brief Show a screen on the display
 * \param screen Game screen to be shown
 */
void Game_ShowScreen(Game_Screen_e screen);

/*!
 * \brief Paint bottom line for temperature and humidity
 * \param
 */

#if PL_CONFIG_USE_PARTIAL_UPDATE
void PaintBottomBar(float temperature, float humidity);
#endif

/*!
 * \brief View de-initialization
 */
void Game_ViewDeinit(void);

/*!
 * \brief Clear Screen
 */
void Game_ClearScreen(void);

/*!
 * \brief View initialization
 */
void Game_ViewInit(void);

#endif /* GAMEVIEW_H_ */
