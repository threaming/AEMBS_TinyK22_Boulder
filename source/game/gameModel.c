/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "game.h"
#include "gameModel.h"
#include "gameView.h"
#include "game.h"
#include "McuUtility.h"
#include <string.h>
#include <assert.h>
#include "sprite.h"
#include "boulder.h"
#include "game/images/boulder_images.h"
#include "game/images/boom0.h"
#include "game/images/boom1.h"

typedef struct GameModel_t {
  GameState_e state;
  Sprite_t *player; /* sprite for the player */
  Sprite_t *boulder; /* list of boulders */
  Sprite_t *diamond; /* list of diamonds */
  Sprite_t *monster; /* list of monsters */
  struct{ // points of the game
	uint32_t nofPoints;
	uint32_t highscore;
  		} points;
} GameModel_t;

static GameModel_t game; /* the game data */

GameState_e Game_GetState(void) {
  return game.state;
}

void Game_SetState(GameState_e state) {
  game.state = state;
}

void Game_ResetScore (void){
	game.points.nofPoints = 0;
}

uint32_t Game_GetScore (void){
	return game.points.nofPoints;
}

void Game_AddScore (uint32_t score){
	game.points.nofPoints += score;
}

bool Game_CheckIfGameLost(void) {
	if (game.player == NULL){
		return true;
	}
	return false;
}

bool Game_CheckIfGameWon(void) {
	if (game.player!=NULL && game.diamond==NULL){
		return true;
	}
  return false;
}

void Game_PlayerAction(Game_PlayerAction_e action, Game_Player_Speed_e speed) {
  int x, y;

  switch (action) {
    case Game_Player_Move_Up:
    case Game_Player_Move_Down:
    case Game_Player_Move_Left:
    case Game_Player_Move_Right:
    switch (action) {
      case Game_Player_Move_Up:    x=0;  y=-1; break;
      case Game_Player_Move_Down:  x=0;  y=1; break;
      case Game_Player_Move_Left:  x=-1; y=0; break;
      case Game_Player_Move_Right: x=1;  y=0; break;
      default: x = y = 0; break;
    } /* switch */
    if (speed==Game_Player_Speed_Fast) {
      x = 2*x;
      y = 2*y;
    } else if (speed==Game_Player_Speed_Fastest) {
      x = 4*x;
      y = 4*y;
    }
    Boulder_OnPlayerMove(game.player, &x, &y);
    Sprite_MoveLimitedDisplay(game.player, x, y);
    break;

    default:
      break;
  } /* switch */
}

void Game_FreeSprites(void) {
  int cntr = 0;
  Sprite_t **sprites;

  do {
    sprites = Game_IteratorGetSpriteLists(&cntr);
    if (sprites!=NULL) {
      Sprite_DeleteList(sprites);
    }
  } while(cntr!=0);
}

Sprite_t *Game_GetBoulderList(void) {
  return game.boulder;
}

Sprite_t *Game_GetDiamondList(void) {
  return game.diamond;
}

void MonsterToDiamondCb(Sprite_t *boulder, Sprite_t *monster) {
  /* called for the event that a boulder crashes the monster: add a diamond for it */
  if (monster!=NULL) { /* safety check */
    int monsterTileX, monsterTileY;
    const int matrix[9][2] = { /* matrix around monster, with x/y tile offsets */
        {-1,-1},{0,-1},{1,-1},
        {-1, 0},{0, 0},{1, 0},
        {-1, 1},{0, 1},{1, 1},
    };

    monsterTileX = Boulder_DisplayPosToTilePosX(monster->posX);
    monsterTileY = Boulder_DisplayPosToTilePosX(monster->posY);
    /* replace monster with a diamond */
    Game_CreateBoulderTileSprite(Boulder_Tile_Diamond, Boulder_GetTileToDisplayXPos(monsterTileX), Boulder_GetTileToDisplayYPos(monsterTileY));
    /* generate diamonds around monster */
    for(int i=0; i<sizeof(matrix)/sizeof(matrix[0]); i++) {
      int tileX, tileY;

      tileX = monsterTileX + matrix[i][0];
      tileY = monsterTileY + matrix[i][1];
      if (   Boulder_GetTileFromTilePos(tileX, tileY)==Boulder_Tile_Dirt /* dirt */
          || (Boulder_GetTileFromTilePos(tileX, tileY)==Boulder_Tile_Empty && Boulder_GetSpriteInTileFromListIterated(tileX, tileY, Game_IteratorGetSpriteLists)==NULL) /* no sprite */
          )
      {
        Boulder_SetTileAtTilePos(tileX, tileY, Boulder_Tile_Empty);
        Game_CreateBoulderTileSprite(Boulder_Tile_Diamond,
            Boulder_GetTileToDisplayXPos(tileX),
            Boulder_GetTileToDisplayYPos(tileY)); /* replace dirt tile with a diamond */
      }
    }
  }
}

bool Game_CheckCollisions(void) {
  bool changed = false;
  const PIMAGE boom0 = Boom0_GetImage();
  const PIMAGE boom1 = Boom1_GetImage();
  /* Player on Diamond */
  changed |= Sprite_CheckCollision(
		  &game.player, false, 		// player doesn't get removed
		  &game.diamond, GAME_SCORE_COLLECTED_DIAMOND, 	// get some points for hitting a diamond
		  NULL, boom0, boom1);		// explosiooon
  /* Monster on Player */
  changed |= Sprite_CheckCollision(
		  &game.monster, false,		// player doesn't get removed
		  &game.player, 0,			// fuckn monster
		  NULL, boom0, boom1);
  /* Boulder on Monster */
  changed |= Sprite_CheckCollision(
		  &game.boulder, true,		// both die
		  &game.monster, GAME_SCORE_DESTROYED_MONSTER,
		  MonsterToDiamondCb, boom0, boom1);
  /* Boulder on Player */
  changed |= Sprite_CheckCollision(
  		  &game.boulder, false,		// both die
  		  &game.player, 0,
  		  NULL, boom0, boom1);

  return changed;
}

bool Game_AgeAndCheckIfAlive(void) {
  bool changed = false;
  int cntr = 0;
  Sprite_t **sprites;

  do {
    sprites = Game_IteratorGetSpriteLists(&cntr);
    if (sprites!=NULL) {
      changed |= Sprite_AgeAndCheckIfAlive(sprites);
    }
  } while(cntr!=0);
  return changed;
}

Sprite_t **Game_IteratorGetSpriteLists(int *cntr) {
  Sprite_t **sprites;

  switch(*cntr) {
    case 0: sprites = &game.player;   (*cntr)++; break;
    case 1: sprites = &game.boulder;  (*cntr)++; break;
    case 2: sprites = &game.diamond;  (*cntr)++; break;
    case 3: sprites = &game.monster;  (*cntr)++; break;
    default: sprites = NULL; (*cntr) = 0; /* end of list */ break;
  }
  return sprites;
}

void Game_CreateBoulderTileSprite(Boulder_Tile_e tile, int x, int y) {
  PIMAGE image; /* is in FLASH! */
  PIMAGE image0 = NULL; /* is in FLASH! */
  Sprite_t *sprite, **list;
  SpriteImage_t *sprite_images = NULL;
  int xOffset, yOffset;

  xOffset = yOffset = 0;
  switch(tile) {
    case Boulder_Tile_Player:
      image = BoulderImages_GetPlayer();
      image0 = BoulderImages_GetPlayerAnim0();
      list = &game.player;
      break;
    case Boulder_Tile_Boulder:
      image = BoulderImages_GetBoulder();
      list = &game.boulder;
      break;
    case Boulder_Tile_Diamond:
      image = BoulderImages_GetDiamond();
      list = &game.diamond;
      break;
    case Boulder_Tile_Monster:
      image = BoulderImages_GetMonster();
      image0 = BoulderImages_GetMonsterAnim0();
      list = &game.monster;
      break;
    default:
      return;
  } /* switch */
  if (image->height<BOULDER_TILE_PIXEL_SIZE) { /* place it on the bottom */
    yOffset = BOULDER_TILE_PIXEL_SIZE-image->height;
  }
  sprite_images = Sprite_NewImageFromROM(image);
  if (image0!=NULL) { /* animation image */
    Sprite_ImageAddToList(&sprite_images, Sprite_NewImageFromROM(image0));
  }
  sprite = Sprite_New(sprite_images, x+xOffset, y+yOffset);
  if (image0!=0) {
    sprite->anim.animate = true;
    sprite->anim.delayCntr = 0;
    sprite->anim.delayCntrReload = 4;
  }
  Sprite_AddToList(list, sprite);
}

static bool SpriteIsTileAlignedX(Sprite_t *sprite) { /* is sprite is aligned on tile grid */
  return (sprite->posX%BOULDER_TILE_PIXEL_SIZE)==0;
}

static bool SpriteIsTileAlignedY(Sprite_t *sprite) { /* is sprite is aligned on tile grid */
  return (sprite->posY%BOULDER_TILE_PIXEL_SIZE)==0;
}

static void HandleFallingItems(Sprite_t *list) {
  /* Go through a list of items (diamonds, boulders) and check if they can fall down.
   * They can fall down if the space below is empty. So a monster or a player can stay below a boulder/diamond,
   * and if the diamond/boulder is not moving yet, it is kept in place.
   */
  Sprite_t *sprite, *down;
  int tileX, tileY; /* falling down item tiles */
  Boulder_Tile_e tileKindBelow;

  sprite = list;
  while(sprite!=NULL) {
    tileX = Boulder_DisplayPosToTilePosX(sprite->posX);
    tileY = Boulder_DisplayPosToTilePosX(sprite->posY);
    tileKindBelow = Boulder_GetTileFromTilePos(tileX, tileY+1); /* check lower tile */
    if (!Sprite_IsMoving(sprite) && SpriteIsTileAlignedX(sprite)) { /* not falling down yet and aligned to a tile? Check if we can start moving */
      if (tileKindBelow==Boulder_Tile_Empty) { /* empty space? check for sprite in it */
        down = Sprite_GetSpriteInPixelAreaIterated(Game_IteratorGetSpriteLists,
            sprite->posX, sprite->posY+BOULDER_TILE_PIXEL_SIZE,
            sprite->posX+BOULDER_TILE_PIXEL_SIZE-1, sprite->posY+BOULDER_TILE_PIXEL_SIZE+BOULDER_TILE_PIXEL_SIZE-1);
        if (down==NULL) { /* no sprite there, start falling down */
          sprite->move.y = 1;
          sprite->move.delayCntr = 0;
          sprite->move.delayCntrReload = 0;
        }
      }
    } else if (sprite->move.y>0 && ((sprite->posY+sprite->images->image->height)%BOULDER_TILE_PIXEL_SIZE)==0) { /* already falling down and on bottom of tile: check if we should stop it */
      /* check items which drop from a pile: they fall left or right */
      if (sprite->move.x!=0) { /* falling down to the right or left */
        /* It must have moved left or right already, otherwise it would not be at the boundary of the tile.
         * So whatever is around, we cans top moving diagonally, we have to change direction down */
        sprite->move.x = 0; /* stop moving in x direction */
      }
      if (tileKindBelow!=Boulder_Tile_Empty) {
        sprite->move.x = 0; /* stop moving */
        sprite->move.y = 0;
      } else { /* check if we have a sprite in there */
        down = Sprite_GetSpriteInPixelAreaIterated(Game_IteratorGetSpriteLists,
            sprite->posX, sprite->posY+BOULDER_TILE_PIXEL_SIZE,
            sprite->posX+BOULDER_TILE_PIXEL_SIZE-1, sprite->posY+BOULDER_TILE_PIXEL_SIZE+BOULDER_TILE_PIXEL_SIZE-1);
        if (down!=NULL) { /* we do have a sprite below it? */
          if (Sprite_IsInList(down, game.boulder) || Sprite_IsInList(down, game.diamond)) { /* if diamond or boulder: don't move any more */
            sprite->move.x = 0; /* stop moving */
            sprite->move.y = 0;
          }
        }
      }
    }
    sprite = sprite->next;
  } /* while */
}

static Sprite_t *GetDiamondOrBoulderSprite(int targetTileX, int targetTileY) {
  Sprite_t *sprite;

  sprite = Boulder_GetSpriteInTileFromList(targetTileX, targetTileY, Game_GetBoulderList());
  if (sprite==NULL) { /* no boulder: check for diamond */
    sprite = Boulder_GetSpriteInTileFromList(targetTileX, targetTileY, Game_GetDiamondList());
  }
  return sprite;
}

static void ChangeMonsterMoving(Sprite_t *sprite) {
  int tileX, tileY; /* tile of monster */
  int targetTileX, targetTileY;
  int32_t r; /* 0: left, 1: right, 2: up, 3: down */
  Boulder_Tile_e tile;

  tileX = Boulder_DisplayPosToTilePosX(sprite->posX);
  tileY = Boulder_DisplayPosToTilePosY(sprite->posY);
  r = McuUtility_random(0, 3); /* pick a random new direction */
  switch(r) {
    case 0: tile = targetTileX = tileX-1; targetTileY = tileY;   tile= Boulder_GetTileFromTilePos(targetTileX, targetTileY); break; /* left */
    case 1: tile = targetTileX = tileX+1; targetTileY = tileY;   tile= Boulder_GetTileFromTilePos(targetTileX, targetTileY); break; /* right */
    case 2: tile = targetTileX = tileX;   targetTileY = tileY-1; tile= Boulder_GetTileFromTilePos(targetTileX, targetTileY); break; /* up */
    case 3: tile = targetTileX = tileX;   targetTileY = tileY+1; tile= Boulder_GetTileFromTilePos(targetTileX, targetTileY); break; /* down */
    default: tile = Boulder_Tile_None; targetTileX = targetTileY = -1; break;
  }
  if (tile==Boulder_Tile_Empty) {
    if (GetDiamondOrBoulderSprite(targetTileX, targetTileY)==NULL) { /* only if there is no boulder or diamond */
      switch(r) {
       case 0: /* left */
         if (SpriteIsTileAlignedY(sprite)) { /* only change direction if aligned */
           sprite->move.x = -1; sprite->move.y = 0;
         }
         break;
       case 1: /* right */
         if (SpriteIsTileAlignedY(sprite)) { /* only change direction if aligned */
           sprite->move.x = 1; sprite->move.y = 0;
         }
         break;
       case 2: /* up */
         if (SpriteIsTileAlignedX(sprite)) { /* only change direction if aligned */
           sprite->move.x = 0; sprite->move.y = -1;
         }
         break;
       case 3: /* down */
         if (SpriteIsTileAlignedX(sprite)) { /* only change direction if aligned */
           sprite->move.x = 0; sprite->move.y = 1;
         }
         break;
       default:
         sprite->move.x = 0; sprite->move.y = 0;
         break;
      }
    } else { /* there is a sprite: stop moving */
      sprite->move.x = 0;
      sprite->move.y = 0;
    }
  } /* if */
}

void Game_HandleMonsterMoving(void) {
  Sprite_t *sprite;
  int tileX, tileY; /* falling down item tiles */
  int targetTileX, targetTileY;
  Boulder_Tile_e tile;

  sprite = game.monster;
  while(sprite!=NULL) {
    if (!Sprite_IsMoving(sprite)) { /* not moving (yet) */
      ChangeMonsterMoving(sprite);
    } else { /* moving: check if we should stop */
      if (sprite->move.x!=0 && SpriteIsTileAlignedX(sprite)) { /* moving horizontally: check if we can continue */
        tileX = Boulder_DisplayPosToTilePosX(sprite->posX);
        tileY = Boulder_DisplayPosToTilePosY(sprite->posY);
        if (sprite->move.x>0) {
          targetTileX = tileX+1;
          targetTileY = tileY;
        } else {
          targetTileX = tileX-1;
          targetTileY = tileY;
        }
        tile = Boulder_GetTileFromTilePos(targetTileX, targetTileY);
        if (tile!=Boulder_Tile_Empty) {
          sprite->move.x = 0; /* stop moving */
          sprite->move.y = 0;
        } else { /* possibly change direction */
          if (GetDiamondOrBoulderSprite(targetTileX, targetTileY)!=NULL) {
            sprite->move.x = 0; /* stop moving because of boulder or diamond */
            sprite->move.y = 0;
          } else {
            ChangeMonsterMoving(sprite);
          }
        }
      } else if (sprite->move.y!=0 && SpriteIsTileAlignedY(sprite)) { /* moving vertically */
        tileX = Boulder_DisplayPosToTilePosX(sprite->posX);
        tileY = Boulder_DisplayPosToTilePosY(sprite->posY);
        if (sprite->move.y>0) {
          targetTileX = tileX;
          targetTileY = tileY+1;
        } else {
          targetTileX = tileX;
          targetTileY = tileY-1;
        }
        tile = Boulder_GetTileFromTilePos(targetTileX, targetTileY);
        if (tile!=Boulder_Tile_Empty) {
          sprite->move.x = 0; /* stop moving */
          sprite->move.y = 0;
        } else {
          if (GetDiamondOrBoulderSprite(targetTileX, targetTileY)!=NULL) {
            sprite->move.x = 0; /* stop moving because of boulder */
            sprite->move.y = 0;
          } else {
            ChangeMonsterMoving(sprite);
          }
        }
      }
    } /* if moving or not */
    sprite = sprite->next;
  } /* while */
}

static void HandlePiledUpItems(Sprite_t *list) {
  Sprite_t *sprite;
  int tileX, tileY;

  sprite = list;
  while (sprite!=NULL) {
    if (!Sprite_IsMoving(sprite)) { /* only if not already moving */
      tileX = Boulder_DisplayPosToTilePosX(sprite->posX);
      tileY = Boulder_DisplayPosToTilePosY(sprite->posY);
      /* check if we are on top of a boulder or diamond */
      if (GetDiamondOrBoulderSprite(tileX, tileY+1)!=NULL) { /* we stand on a boulder or diamond */
        /* check first left side */
        if (   Boulder_GetTileFromTilePos(tileX-1, tileY)==Boulder_Tile_Empty /* left is empty */
            && Boulder_GetTileFromTilePos(tileX-1, tileY+1)==Boulder_Tile_Empty /* lower-left is empty */
            && Boulder_GetSpriteInTileFromListIterated(tileX-1, tileY, Game_IteratorGetSpriteLists)==NULL /* no sprite on the left side */
            && GetDiamondOrBoulderSprite(tileX-1, tileY+1)==NULL /* no boulder or diamond on the lower-left */
           )
        {
          sprite->move.x = -1;
          sprite->move.y = 1;
        } else if (  /* check right side */
               Boulder_GetTileFromTilePos(tileX+1, tileY)==Boulder_Tile_Empty /* left is empty */
            && Boulder_GetTileFromTilePos(tileX+1, tileY+1)==Boulder_Tile_Empty /* lower-right is empty */
            && Boulder_GetSpriteInTileFromListIterated(tileX+1, tileY, Game_IteratorGetSpriteLists)==NULL /* no sprite on the left side */
            && GetDiamondOrBoulderSprite(tileX+1, tileY+1)==NULL /* no boulder or diamond on the lower-right */
           )
        {
          sprite->move.x = 1;
          sprite->move.y = 1;
        }
      }
    }
    sprite = sprite->next;
  }
}

void Game_HandleFallingItems(void) {
  /* both boulders and diamonds can fall down into empty space */
  HandleFallingItems(game.boulder);
  HandleFallingItems(game.diamond);
  HandlePiledUpItems(game.boulder);
  HandlePiledUpItems(game.diamond);
}

void Game_New(uint8_t gameLevel) {
	Sprite_DeleteList(&game.monster);
	Sprite_DeleteList(&game.diamond);
	Sprite_DeleteList(&game.player);
	Sprite_DeleteList(&game.boulder);
	Boulder_CreateLevel(gameLevel); /* player will be created here too */
}

void Game_ModelDeinit(void) {
	game.state = GAME_STATE_INTRO;
	Sprite_DeleteList(&game.monster);
	Sprite_DeleteList(&game.diamond);
	Sprite_DeleteList(&game.player);
	Sprite_DeleteList(&game.boulder);
	Boulder_Deinit();
}

void Game_ModelInit(void) {
  Boulder_Init();
}
