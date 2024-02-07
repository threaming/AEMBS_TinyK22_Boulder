/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BOULDER_H_
#define BOULDER_H_

#include <stdint.h>
#include "sprite.h"

/* display size in pixels */
#define BOULDER_DISPLAY_CONFIG_WITH     (128)
#define BOULDER_DISPLAY_CONFIG_HEIGHT   (64)

/* setting of boulder field */
#define BOULDER_TILE_PIXEL_SIZE      (8) /* a field in the game is this pixel wide and high */
#define BOULDER_TILE_NOF_X           (BOULDER_DISPLAY_CONFIG_WITH/BOULDER_TILE_PIXEL_SIZE)
#define BOULDER_TILE_NOF_Y           (BOULDER_DISPLAY_CONFIG_HEIGHT/BOULDER_TILE_PIXEL_SIZE)

typedef enum Boulder_Tile_e {
  Boulder_Tile_None,       /*!< used for outside or undefined tiles */
  Boulder_Tile_Player,     /*!< the player */
  Boulder_Tile_Dirt,       /*!< dirt, removable */
  Boulder_Tile_Diamond,    /*!< the diamonds to collect */
  Boulder_Tile_Boulder,    /*!< a rock which can fall down */
  Boulder_Tile_Wall,       /*!< a solid wall */
  Boulder_Tile_Monster,    /*!< ups! a monster */
  Boulder_Tile_Empty,      /*!< hollow part */
} Boulder_Tile_e;

/*!
 * \brief Sets the tile kind at a given tile position
 * \param boulderTileX Tile x coordinate
 * \param boulderTileY Tile y coordinate
 * \param tile Tile kind to be assigned
 */
void Boulder_SetTileAtTilePos(int8_t boulderTileX, int8_t boulderTileY, Boulder_Tile_e tile);

/*!
 * \brief Return the tile kind at a given tile position
 * \param boulderTileX Tile x position
 * \param boulderTileY Tile y position
 * \return The tile kind at that position
 */
Boulder_Tile_e Boulder_GetTileFromTilePos(int8_t boulderTileX, int8_t boulderTileY);

/*!
 * \brief Return the tile kind at a given display position
 * \param x Display x coordinate
 * \param y Display y coordinate
 * \return The tile kind at the given coordinate
 */
Boulder_Tile_e Boulder_GetTileFromDisplayPos(int x, int y);

/*!
 * \brief Return for a given tile x position the display x coordinate.
 * \param boulderTileX Tile x position
 * \return Display x coordinate
 */
int8_t Boulder_GetTileToDisplayXPos(int8_t boulderTileX);

/*!
 * \brief Return for a given tile y position the display y coordinate.
 * \param boulderTileY Tile y position
 * \return Display y coordinate
 */
int8_t Boulder_GetTileToDisplayYPos(int8_t boulderTileY);

/*!
 * \brief Returns from a display x position the corresponding tile x position.
 * \param posX Display x position
 * \return Tile x position
 */
int Boulder_DisplayPosToTilePosX(int posX);

/*!
 * \brief Returns from a display y position the corresponding tile y position.
 * \param posY Display y position
 * \return Tile y position
 */
int Boulder_DisplayPosToTilePosY(int posY);

/*!
 * \brief Return the sprite present in a tile, using a list of sprite to search through
 * \param xTile Tile x position
 * \param yTile Tile y position
 * \param list List of sprites to search
 * \return The first sprite found in in this tile, otherwise NULL
 */
Sprite_t *Boulder_GetSpriteInTileFromList(int xTile, int yTile, Sprite_t *list);

/*!
 * \brief Return the sprite present in a tile, using a sprite list iterator to search through
 * \param xTile Tile x position
 * \param yTile Tile y position
 * \param iteratorFct Iterator function to iterate through the list(s)
 * \return The first sprite found in in this tile, otherwise NULL
 */
Sprite_t *Boulder_GetSpriteInTileFromListIterated(int xTile, int yTile, Sprite_IteratorGetSpriteListFunction iteratorFct);

/*!
 * \brief Called to move the player. It uses in/out x/y coordinates as input/output and returns the allowed moving pixels.
 * \param sprite Player sprite to move
 * \param deltaX On input, this is the desired x (display coordinates) to move the player. On return, this contains the allowed moving pixels.
 * \param deltaY On input, this is the desired y (display coordinates) to move the player. On return, this contains the allowed moving pixels.
 */
void Boulder_OnPlayerMove(Sprite_t *sprite, int *deltaX, int *deltaY);

/*!
 * \brief Function to paint all tiles in the game which are not handled by sprites.
 */
void Boulder_PaintTiles(void);

/*!
 * \brief Creates the tiles and sprites for a new level. Data of previous levels is not deallocated by this function.
 * \param level Level number, starting with zero.
 */
void Boulder_CreateLevel(uint8_t level);

/*!
 * \brief Module de-initialization
 */
void Boulder_Deinit(void);

/*!
 * \brief Module initialization
 */
void Boulder_Init(void);

#endif /* BOULDER_H_ */
