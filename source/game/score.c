/*
 * score.c
 *
 *  Created on: 23.06.2023
 *      Author: joelv
 */

#include "score.h"
#include "McuSystemView.h"


typedef struct GameScore_t {
  uint32_t session;
  uint32_t highscore;
} GameScore_t;

static GameScore_t score;
static bool new_highscore;

void Score_Init(void) {
  score.session = 0;
  score.highscore = 0;
  new_highscore = false;
}

void Score_AddGameScore(uint32_t add_score) {
  score.session += add_score;

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SEGGER_SYSVIEW_PrintfTarget("score + add = %d\n", score.session);
#endif

  // check if the new score is highscore worthy
  if(score.session > score.highscore) {
    new_highscore = true;
    Score_SetHighscore(score.session);
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
    SEGGER_SYSVIEW_PrintfTarget("new highscore = %d\n", score.highscore);
#endif
  }
}

// returns the current amount of points
uint32_t Score_GetGameScore(void) { return score.session; }

// Highcore Functions
void Score_SetHighscore(uint32_t new_score) { score.highscore = new_score; }
bool Score_GetIsNewHighscore(void) { return new_highscore; }
bool Score_ResetIsNewHighscore(void) { new_highscore = false; }

// returns the highscore of the whole session
uint32_t Score_GetHighscore(void) { return score.highscore; }

void Score_ResetHighscore(void) { score.highscore = 0; }
void Score_ResetGameScore(void) {
  score.session = 0;
  new_highscore = false;
}
