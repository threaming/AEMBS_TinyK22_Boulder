/*
 * game.c
 *
 * Implementing game task according to AEMBS Lab
 *
 *  Created on: 04.04.2023
 *      Author: Ming
 */
#include "game/game.h"
#include "leds.h"
#include "McuRTOS.h"
#include "queue.h"
#include "timers.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "game/images/boulder_images.h"
#include "game/sprite.h"
#include "game/gameModel.h"
#include "game/gameView.h"
#include "game/boulder.h"
#include "hat/sensor.h"
#include "McuSSD1306.h"
#include "McuGDisplaySSD1306.h"
#include "McuGFont.h"
#include "McuUtility.h"
#include "game/score.h"

/* Queue definitions */
#define EVENT_QUEUE_LENGTH		(30) 						// # of elements in queue
#define EVENT_QUEUE_ELEM_SIZE	(sizeof(Game_event_t))		// size of a queue item

/* Global game variables */
typedef struct Game_event_t {
	Game_event_kind_e kind; 	// Kind of event, Data is inside union
	union u_ {
		struct{	// for Game_Event_Kind_Button
			BTN_Buttons_e button; /* button of the event */
			McuDbnc_EventKinds kind; /* kind of button event */
		} btn;
		struct{ // points of the game
			int nofPoints;
		} points;
	} u;
} Game_event_t;
static QueueHandle_t game_eventQueue; // Queue handle
static TaskHandle_t gameHndl = NULL;
static TimerHandle_t gameTimer = NULL;
static uint8_t gameLevel = 0; /* number of the level */

/* Helper function for sending Events */
void Game_SendEvent(Game_event_t *event){
	if (xQueueSendToBack(game_eventQueue, event, pdMS_TO_TICKS(500)) != pdPASS){
	#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
			McuSystemView_Error((const char*)"failed to send GameEvent, queue full?\r\n");
	#endif
	}
}

/* Timer definitions */
static void GameUpdater2000(TimerHandle_t pxTimer){
	bool changed = false;

	/* do some gamy stuff */
	changed |= Game_AgeAndCheckIfAlive();
	changed |= Game_CheckCollisions();
	Game_HandleFallingItems();
	Game_HandleMonsterMoving();

	Game_event_t GameEvent;
	/* Check Status */
	if(Game_CheckIfGameWon()){
		GameEvent.kind = Game_Event_Kind_Game_Won;
		Game_SendEvent(&GameEvent);
		xTimerStop(gameTimer, portMAX_DELAY); // Stop refreshing
	}
	else if (Game_CheckIfGameLost()){
		GameEvent.kind = Game_Event_Kind_Game_Lost;
		Game_SendEvent(&GameEvent);
		xTimerStop(gameTimer, portMAX_DELAY); // Stop refreshing
	}
	else {
		/* get the FPS */
		GameEvent.kind = Game_Event_Kind_Update_View;
		Game_SendEvent(&GameEvent);
	}
}

static void waitForKeyPress(void){
	BaseType_t res;
	Game_event_t event;

	while(true){
		res = xQueueReceive(game_eventQueue, &event, portMAX_DELAY);	// blocking for a entry
		if (res == pdTRUE){
			/* get game event kind */
			switch(event.kind){
			case Game_Event_Kind_Button:
				return;
			default:
				break;
			}
		}
	}
}

/*
 * receive button events form "debounce.c" module
 *
 */
void Game_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind) {
	Game_event_t GameEvent;

	GameEvent.kind = Game_Event_Kind_Button;
	GameEvent.u.btn.button = button;
	GameEvent.u.btn.kind = kind;
	Game_SendEvent(&GameEvent);
}

/*
 * Score change
 */
void Game_ScoreEvent(uint32_t score){
	Game_event_t GameEvent;

	GameEvent.kind = Game_Event_Kind_New_Score;
	GameEvent.u.points.nofPoints = score;
	Game_SendEvent(&GameEvent);
}

/*
 * Task for controlling the game
 */
static void gameTask(void *pv){
	Game_event_t event, startEvent;
	BaseType_t res;

	vTaskDelay(pdMS_TO_TICKS(250));	// give devices time to power up
	Sensor_Init();
	Game_ViewInit();
	if(sLock()){
		McuSSD1306_Init();
		McuGDisplaySSD1306_Init();
		sUnlock();
	}

	Game_ShowScreen(GAME_SCREEN_AEMBS);
	vTaskDelay(pdMS_TO_TICKS(500));
	//Game_ClearScreen();
	Game_ShowScreen(GAME_SCREEN_GRAPHICS);
	vTaskDelay(pdMS_TO_TICKS(500));
	Game_ShowScreen(GAME_SCREEN_TEMPERATURE);
	vTaskDelay(pdMS_TO_TICKS(500));

	startEvent.kind = Game_Event_Kind_Game_Start;
	Game_SendEvent(&startEvent);

	/* Main Task */
	while (true) {
		res = xQueueReceive(game_eventQueue, &event, portMAX_DELAY);	// blocking for a event
		if (res == pdTRUE){
			/* get game event kind */
			switch(event.kind){
				case Game_Event_Kind_Game_Start:
					Game_ResetScore();
					Game_New(gameLevel);
					Game_ShowScreen(GAME_SCREEN_GAMEPLAY);
					if (xTimerStart(gameTimer, portMAX_DELAY) != pdTRUE) {
					#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
						McuSystemView_Error((const char*)"failed to start timer!?\r\n");
					#endif
						while(true){};
					} // Start refreshing
					break;
				/* Button pressed ! */
				case Game_Event_Kind_Button:
					switch(event.u.btn.button){
						case BTN_NAV_UP:
							if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED) {
								Game_PlayerAction(Game_Player_Move_Up, Game_Player_Speed_Normal);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Up, Game_Player_Speed_Fast);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_LONG_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Up, Game_Player_Speed_Fastest);
							}
							break;
						case BTN_NAV_DOWN:
							if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED) {
								Game_PlayerAction(Game_Player_Move_Down, Game_Player_Speed_Normal);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Down, Game_Player_Speed_Fast);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_LONG_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Down, Game_Player_Speed_Fastest);
							}
							break;
						case BTN_NAV_LEFT:
							if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED) {
								Game_PlayerAction(Game_Player_Move_Left, Game_Player_Speed_Normal);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Left, Game_Player_Speed_Fast);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_LONG_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Left, Game_Player_Speed_Fastest);
							}
							break;
						case BTN_NAV_RIGHT:
							if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED) {
								Game_PlayerAction(Game_Player_Move_Right, Game_Player_Speed_Normal);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Right, Game_Player_Speed_Fast);
							} else if (event.u.btn.kind==MCUDBNC_EVENT_LONG_PRESSED_REPEAT) {
								Game_PlayerAction(Game_Player_Move_Right, Game_Player_Speed_Fastest);
							}
							break;
						case BTN_NAV_CENTER:
							break;
						default:
							break;
					}
					break;
				/* Have to update the viewwwws */
				case Game_Event_Kind_Update_View:
					Game_ShowScreen(GAME_SCREEN_GAMEPLAY);
					break;

				/* Won the game */
				case Game_Event_Kind_Game_Won:
//					Game_ShowScreen(GAME_SCREEN_WON);
//					Game_ShowScreen(GAME_SCREEN_WON_SCORE);
					Game_ShowScreen(GAME_SCREEN_SCORE);
					waitForKeyPress();
					startEvent.kind = Game_Event_Kind_Game_Start;	// restart Game
					if(gameLevel < GAME_CONFIG_NOF_LEVEL-1){
						gameLevel++;
					}
					Game_SendEvent(&startEvent);
					break;

				/* Lost the game */
				case Game_Event_Kind_Game_Lost:
//					Game_ShowScreen(GAME_SCREEN_LOST);
//					Game_ShowScreen(GAME_SCREEN_LOST_SCORE);
					Game_ShowScreen(GAME_SCREEN_SCORE);
					waitForKeyPress();
					startEvent.kind = Game_Event_Kind_Game_Start;	// restart Game
					gameLevel = 0;
					Score_ResetGameScore();
					Game_SendEvent(&startEvent);
					break;

				/* Score update */
				case Game_Event_Kind_New_Score:
					Game_AddScore(event.u.points.nofPoints);
				default:
					break;
			}
		}
		else{	// No Message Received --> Error!?
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
			McuSystemView_Error((const char*)"failed to receive GameEvent, portMAX_DELAY reached?\r\n");
#endif
		}
		LEDS_Neg(LEDS_GREEN);
		/* Mom, I can't pause, it's online! " */
		//vTaskSuspend(gameHndl);
		/* Oh yes I can, dear */
		//vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/*
 * Task for working with button events
 */
//static void Game_OnButtonTask(void *pvParameters){
//	bool buttonPressed;
//	GameEventData_t GameEvent;
//
//	for(;;) {
//		if (xQueueReceive(game_eventQueue, &GameEvent, pdMS_TO_TICKS(100))!=pdPASS){
//#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
//			McuSystemView_Warn((const char*)"failed to receive GameEvent, queue empty?\r\n");
//#endif
//		}
//		buttonPressed = GameEvent.button==BTN_NAV_CENTER && GameEvent.kind==MCUDBNC_EVENT_PRESSED;
//
//		if (buttonPressed) {
//			LEDS_On(LEDS_ORANGE);
//			vTaskDelay(pdMS_TO_TICKS(50)); /* give back some time to see the LED blinking */
//			LEDS_Off(LEDS_ORANGE);
//		}
//		vTaskDelay(pdMS_TO_TICKS(100));
//	}
//}

/*
 * Initialize game
 *
 */
void Game_Init(void){
	Score_Init();
	BaseType_t res;

	/* Create Queue */
	game_eventQueue = xQueueCreate(EVENT_QUEUE_LENGTH, EVENT_QUEUE_ELEM_SIZE);
	if (game_eventQueue == NULL) {	// Error detection
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_Error((const char*)"failed to create queue, no memory?\r\n");
#endif
		for(;;) {} // out of memory?
	}
	vQueueAddToRegistry(game_eventQueue, "GameEvent_Queue");	// for debugging

	/* Create Game Task */
	res = xTaskCreate(
			gameTask,	// from game.h
			"gameTask",
			800/sizeof(StackType_t),
			NULL,
			tskIDLE_PRIORITY+1, // Priority: medium
			&gameHndl);
	if (res!=pdPASS) {	// Error detection
	    /* error! */
	    for(;;) {}
	  }

	/* Create Timer */
	gameTimer = xTimerCreate(
			"gameTimer 150ms",
			pdMS_TO_TICKS(150),
			pdTRUE,
			(void*) 2,
			GameUpdater2000);
	if (gameTimer == NULL){
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
		McuSystemView_Error((const char*)"failed to create timer, no memory?\r\n");
#endif
		for(;;) {} // out of memory?
	}

	/* set randomness */
	float t, h;
	GetTemp(&t);
	GetHum(&h);
	McuUtility_randomSetSeed((int)(t+h*10.0));
}

/*
 * Deinitialize game
 *
 * nothing to do here yet
 */
void Game_Deinit(void){

}

