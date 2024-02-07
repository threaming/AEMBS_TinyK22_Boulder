/*
 * game.h
 *
 *  Created on: 04.04.2023
 *      Author: Ming
 */

#ifndef GAME_GAME_H_
#define GAME_GAME_H_

#include "buttons/buttons_config.h"
#include "McuDebounce.h"

typedef enum Game_event_kind_e {
	Game_Event_Kind_None,			// Initialization value
	Game_Event_Kind_Game_Start,		// Start a game
	Game_Event_Kind_Update_View,	// request to update view
	Game_Event_Kind_Game_Lost,		// game lost
	Game_Event_Kind_Game_Won,		// winning the game
	Game_Event_Kind_Button,			// button pressed
	Game_Event_Kind_New_Score		// earned some points?
} Game_event_kind_e;

void Game_Init(void);

void Game_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind);

void Game_ScoreEvent(uint32_t score);

void Game_Deinit(void);

#endif /* GAME_GAME_H_ */
