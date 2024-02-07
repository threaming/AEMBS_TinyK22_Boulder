/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "game/game_config.h"
#include "game/game.h"
#include "game/gameView.h"
#include "game/gameModel.h"
#include "game/sprite.h"
#include "McuUtility.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuFontHelv08Normal.h"
#include "McuFontHelv08Bold.h"
#include "McuFontHelv10Normal.h"
#include "McuFontHelv12Normal.h"
#include "McuFontHelv12Bold.h"
#include "McuFontHelv18Bold.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#include "game/boulder.h"
#include "game/images/boulder_images.h"
#include "game/score.h"
#include "hat/sensor.h"

/* Global Variables */
static float temp;	// Temperature of SHT40

#if PL_CONFIG_USE_PARTIAL_UPDATE
static SemaphoreHandle_t dispBufMutex = NULL; /* Mutex to protect access to display buffer */

void DispBuf_Lock(void) {
  if (xSemaphoreTakeRecursive(dispBufMutex, portMAX_DELAY)!=pdTRUE) {
    for(;;) { /* error? */ }
  }
}

void DispBuf_Unlock(void) {
  if (xSemaphoreGiveRecursive(dispBufMutex)!=pdTRUE) {
    for(;;) { /* error? */ }
  }
}
#endif

/*!
 * \brief Shows one line of text centered on the display, with a border around it
 * \param text0 Line one of text
 */
static void Show1Liner(const unsigned char *text0) {
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Lock();
  McuGDisplaySSD1306_DrawFilledBox(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE, McuGDisplaySSD1306_COLOR_PIXEL_CLR);
#else
  McuGDisplaySSD1306_Clear();
#endif
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth((unsigned char*)text0, font, NULL)/2;
  y = McuGDisplaySSD1306_GetHeight()/2 - charHeight/2; /* 1 line */
  McuFontDisplay_WriteString((unsigned char*)text0, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-1-4, McuGDisplaySSD1306_GetHeight()-1-4, 1, McuGDisplaySSD1306_COLOR_BLUE);
  if(sLock()){
	#if PL_CONFIG_USE_PARTIAL_UPDATE
	  McuGDisplaySSD1306_UpdateRegion(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE);
	#else
	  McuGDisplaySSD1306_UpdateFull();
	#endif
	sUnlock();
  }
#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Unlock();
#endif
}

/*!
 * \brief Shows two lines of text centered on the display, with a border around it
 * \param text0 Line one of text
 * \param text1 Line two of text
 */
static void Show2Liner(const unsigned char *text0, const unsigned char *text1) {
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Lock();
  McuGDisplaySSD1306_DrawFilledBox(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE, McuGDisplaySSD1306_COLOR_PIXEL_CLR);
#else
  McuGDisplaySSD1306_Clear();
#endif
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth((unsigned char*)text0, font, NULL)/2;
  y = McuGDisplaySSD1306_GetHeight()/2 - (2*charHeight)/2; /* 2 lines */
  McuFontDisplay_WriteString((unsigned char*)text0, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth()/2 - McuFontDisplay_GetStringWidth((unsigned char*)text1, font, NULL)/2;
  y += McuGDisplaySSD1306_GetHeight()/2 - (2*charHeight)/2;
  McuFontDisplay_WriteString((unsigned char*)text1, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-1-4, McuGDisplaySSD1306_GetHeight()-1-4, 1, McuGDisplaySSD1306_COLOR_BLUE);
  if(sLock()){
	#if PL_CONFIG_USE_PARTIAL_UPDATE
	  McuGDisplaySSD1306_UpdateRegion(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE);
	#else
	  McuGDisplaySSD1306_UpdateFull();
	#endif
	sUnlock();
  }
#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Unlock();
#endif
}

static void PaintGamePlayScreen(void) {
#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Lock();
  McuGDisplaySSD1306_DrawFilledBox(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE, McuGDisplaySSD1306_COLOR_PIXEL_CLR);
#else
  McuGDisplaySSD1306_Clear();
#endif
  Boulder_PaintTiles();
  int cntr = 0;
  Sprite_t **sprites;

  do {
    sprites = Game_IteratorGetSpriteLists(&cntr);
    if (sprites!=NULL) {
      Sprite_PaintList(*sprites);
    }
  } while(cntr!=0);
  if(sLock()){
	#if PL_CONFIG_USE_PARTIAL_UPDATE
	  McuGDisplaySSD1306_UpdateRegion(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE);
	#else
	  McuGDisplaySSD1306_UpdateFull();
	#endif
	sUnlock();
  }
#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Unlock();
#endif
}

/* snippet to show Score */
static void PrintScore(const unsigned char *title) {
  PGFONT_Callbacks font_title = McuFontHelv12Bold_GetFont();
  PGFONT_Callbacks font_subtitle = McuFontHelv08Normal_GetFont();
  PGFONT_Callbacks font_score = McuFontHelv08Bold_GetFont();
  McuFontDisplay_PixelDim x, y, info_new_width;
  McuFontDisplay_PixelDim charHeight_title, charHeight_subtitle, charHeight_score, totalHeight_title, totalHeight_subtitle, totalHeight_score;
  uint8_t buf[24];

#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Lock();
  McuGDisplaySSD1306_DrawFilledBox(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE, McuGDisplaySSD1306_COLOR_PIXEL_CLR);
#else
  McuGDisplaySSD1306_Clear();
#endif
  McuFontDisplay_GetFontHeight(font_title, &charHeight_title, &totalHeight_title);
  McuFontDisplay_GetFontHeight(font_subtitle, &charHeight_subtitle, &totalHeight_subtitle);
  McuFontDisplay_GetFontHeight(font_score, &charHeight_score, &totalHeight_score);

  /* print title */
  x = 10;
  y = 10;

  McuFontDisplay_WriteString((unsigned char*)title,
      McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font_title);

  /* print score */
  x = 10;
  y += charHeight_title + 10;
  McuGDisplaySSD1306_DrawLine(10, y - 5, McuGDisplaySSD1306_GetWidth() - 10, y - 5, McuGDisplaySSD1306_COLOR_BLUE);

  McuUtility_Num32uToStr(buf, sizeof(buf), Score_GetGameScore());


  McuFontDisplay_WriteString((unsigned char*) "Score: ",
      McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font_subtitle);
  McuFontDisplay_WriteString((unsigned char*) buf,
      McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font_subtitle);

  /* print highscore */
  x = 10;
  y += charHeight_subtitle;

  McuUtility_Num32uToStr(buf, sizeof(buf), Score_GetHighscore());

  McuFontDisplay_WriteString((unsigned char*) "Best: ",
      McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font_subtitle);
  McuFontDisplay_WriteString((unsigned char*) buf,
      McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font_subtitle);

  info_new_width = McuFontDisplay_GetStringWidth((unsigned char*)"NEW!", font_score, NULL);

  /* if new highscore, add NEW! marker */
  if(Score_GetIsNewHighscore()) {
	Score_ResetIsNewHighscore(); // after reading the flag, clear it
    x = McuGDisplaySSD1306_GetWidth() - 10 - info_new_width;
    McuFontDisplay_WriteString((unsigned char*) "NEW!",
        McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font_score);
  }


  if(sLock()){
	#if PL_CONFIG_USE_PARTIAL_UPDATE
	  McuGDisplaySSD1306_UpdateRegion(0, 0, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE);
	#else
	  McuGDisplaySSD1306_UpdateFull();
	#endif
	sUnlock();
  }
#if PL_CONFIG_USE_PARTIAL_UPDATE
  DispBuf_Unlock();
#endif
}

/* snippet to show temperature on display: */
void ShowTemperature(float value) {
	McuFontDisplay_PixelDim x, y, w, h;
	uint8_t buf[24];

	McuGDisplaySSD1306_Clear();
	McuUtility_NumFloatToStr(buf,  sizeof(buf), value, 2);
	McuUtility_chcat(buf, sizeof(buf), 'C');
	w = McuFontDisplay_GetStringWidth(buf, McuFontHelv18Bold_GetFont(), NULL);
	h = McuFontDisplay_GetStringHeight(buf, McuFontHelv18Bold_GetFont(), NULL);
	x = (McuGDisplaySSD1306_GetWidth()-w)/2;
	y = (McuGDisplaySSD1306_GetHeight()-h)/2;
	McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv18Bold_GetFont());

	McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_WHITE);
	McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-5, McuGDisplaySSD1306_GetHeight()-5, 1, McuGDisplaySSD1306_COLOR_WHITE);
	if(sLock()){
		McuGDisplaySSD1306_UpdateFull();
		sUnlock();
	}
}

/* snippet to show score (form temp) */
void ShowScore(uint32_t score){
	McuFontDisplay_PixelDim x, y, w, h;
	uint8_t buf[24];

	McuGDisplaySSD1306_Clear();
	McuUtility_Num32uToStr(buf, sizeof(buf), score);
	w = McuFontDisplay_GetStringWidth(buf, McuFontHelv18Bold_GetFont(), NULL);
	h = McuFontDisplay_GetStringHeight(buf, McuFontHelv18Bold_GetFont(), NULL);
	x = (McuGDisplaySSD1306_GetWidth()-w)/2;
	y = (McuGDisplaySSD1306_GetHeight()-h)/2;
	McuFontDisplay_WriteString(buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, McuFontHelv18Bold_GetFont());

	McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_WHITE);
	McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth()-5, McuGDisplaySSD1306_GetHeight()-5, 1, McuGDisplaySSD1306_COLOR_WHITE);
	if(sLock()){
		McuGDisplaySSD1306_UpdateFull();
		sUnlock();
	}
}

void Game_ShowScreen(Game_Screen_e screen) {
  switch(screen) {
    /*! \todo extend as needed */
    case GAME_SCREEN_AEMBS:
      Show1Liner((const unsigned char*)"AEMBS");
      break;
    case GAME_SCREEN_GRAPHICS: /*! \todo */
//    	McuGDisplaySSD1306_DrawCircle(20, 30, 5, McuGDisplaySSD1306_COLOR_YELLOW);
//		McuGDisplaySSD1306_DrawLine(0,0,128,64,McuGDisplaySSD1306_COLOR_BRIGHT_GREEN);
//		McuGDisplaySSD1306_DrawLine(110, 12, 115, 40, McuGDisplaySSD1306_COLOR_DARK_RED);
//		McuGDisplaySSD1306_DrawBox(0, 0, 30, 30, 2, McuGDisplaySSD1306_COLOR_WHITE);
//		Show2Liner((const unsigned char*)"ChatGPT:", (const unsigned char*)"this is Python");

    	McuGDisplaySSD1306_Clear();
		McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 1, McuGDisplaySSD1306_COLOR_WHITE);
		McuGDisplaySSD1306_DrawCircle(20 /* x */, 30 /* y */, 5 /* radius */, McuGDisplaySSD1306_COLOR_WHITE);
		McuGDisplaySSD1306_DrawCircle(50 /* x */, 20 /* y */, 15 /* radius */, McuGDisplaySSD1306_COLOR_WHITE);
		McuGDisplaySSD1306_DrawLine(McuGDisplaySSD1306_GetWidth()-1, McuGDisplaySSD1306_GetHeight()-1, 0, 0, McuGDisplaySSD1306_COLOR_WHITE);
		McuGDisplaySSD1306_DrawBox(25, 25, 30, 30, 2, McuGDisplaySSD1306_COLOR_WHITE);
		McuGDisplaySSD1306_DrawLine(50, 10, 60, 20, McuGDisplaySSD1306_COLOR_WHITE);
		McuGDisplaySSD1306_DrawLine(60, 20, 40, 20, McuGDisplaySSD1306_COLOR_WHITE);
		McuGDisplaySSD1306_DrawLine(40, 20, 50, 10, McuGDisplaySSD1306_COLOR_WHITE);

		if(sLock()){
			McuGDisplaySSD1306_UpdateFull();
			sUnlock();
		}
      break;
    case GAME_SCREEN_TEMPERATURE:
    	GetTemp(&temp);
    	ShowTemperature(temp);
      break;
    case GAME_SCREEN_GAMEPLAY:
    	PaintGamePlayScreen();
      break;
    case GAME_SCREEN_WON:
    	Show2Liner((const unsigned char*)"You are a king!", (const unsigned char*)"(press a key!)");
    	break;
    case GAME_SCREEN_WON_SCORE:
          PrintScore((const unsigned char*)"Round won!");
          break;
	case GAME_SCREEN_LOST_SCORE:
          PrintScore((const unsigned char*)"Game Over!");
          break;
    case GAME_SCREEN_LOST:
    	Show2Liner((const unsigned char*)"You lost :-(", (const unsigned char*)"(press a key!)");
		break;
    case GAME_SCREEN_SCORE:
    	ShowScore(Game_GetScore());
    	break;
    default:
      break;
  }
}

#if PL_CONFIG_USE_PARTIAL_UPDATE
void PaintBottomBar(float temperature, float humidity) {
  DispBuf_Lock();
  McuGDisplaySSD1306_DrawFilledBox(0, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, 1*BOULDER_TILE_PIXEL_SIZE, McuGDisplaySSD1306_COLOR_PIXEL_CLR);

  uint8_t buf[32];
  McuFontDisplay_PixelDim x, y;

  x = 0;
  y = BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE;
  buf[0] = '\0';
  McuUtility_strcat(buf,  sizeof(buf), (unsigned char*)"t: ");
  McuUtility_strcatNumFloat(buf, sizeof(buf), temperature, 1);
  McuUtility_strcat(buf,  sizeof(buf), (unsigned char*)"C, h: ");
  McuUtility_strcatNumFloat(buf, sizeof(buf), humidity, 1);
  McuUtility_strcat(buf,  sizeof(buf), (unsigned char*)"%");
  PGFONT_Callbacks font = McuFontHelv08Normal_GetFont();
  McuFontDisplay_WriteString((unsigned char*)buf, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  if(sLock()){
    McuGDisplaySSD1306_UpdateRegion(0, BOULDER_TILE_NOF_Y*BOULDER_TILE_PIXEL_SIZE, BOULDER_TILE_NOF_X*BOULDER_TILE_PIXEL_SIZE, 1*BOULDER_TILE_PIXEL_SIZE);
	sUnlock();
  }
  DispBuf_Unlock();
}
#endif /* PL_CONFIG_USE_PARTIAL_UPDATE */

void Game_ClearScreen(void) {
	McuGDisplaySSD1306_Clear();
	if(sLock()){
		McuGDisplaySSD1306_UpdateFull();
		sUnlock();
	}
}


void Game_ViewInit(void) {
#if PL_CONFIG_USE_PARTIAL_UPDATE
  dispBufMutex = xSemaphoreCreateRecursiveMutex();
  if (dispBufMutex==NULL) {
    for(;;) { /* error */ }
  }
  vQueueAddToRegistry(dispBufMutex, "Disp Mutex");
#endif
}

void Game_ViewDeinit(void) {
#if PL_CONFIG_USE_PARTIAL_UPDATE
  vSemaphoreDelete(dispBufMutex);
  dispBufMutex = NULL;
#endif
}
