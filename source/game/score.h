/*
 * score.h
 *
 *  Created on: 23.06.2023
 *      Author: joelv
 */

#ifndef SCORE_H_
#define SCORE_H_


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


/* Goal: Show player score & highscore between levels and on game over
 * Might need to be reentrant!
 */
void Score_Init(void);

// Player Score Functions
void Score_AddGameScore(uint32_t score);
uint32_t Score_GetGameScore(void);
void Score_ResetGameScore(void);

// Highscore Functions
void Score_SetHighscore(uint32_t score);
uint32_t Score_GetHighscore(void);
void Score_ResetHighscore(void);
bool Score_GetIsNewHighscore(void);
bool Score_ResetIsNewHighscore(void);

#endif /* SCORE_H_ */
