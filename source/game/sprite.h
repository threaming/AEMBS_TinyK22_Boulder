/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "McuGDisplaySSD1306.h"
#include "stdbool.h"

/* structure to describe a sprite image */
typedef struct SpriteImage_t {
  struct SpriteImage_t *prev, *next; /* circular double linked list, used for animations */
  PIMAGE image; /* pointer to image information */
} SpriteImage_t;

/* structure to describe a sprite with all its properties. The sprites can build a linear list (double-linked) */
typedef struct Sprite_t {
  struct Sprite_t *prev, *next; /* double-linked list of sprites */
  SpriteImage_t *images; /* pointer to circular image list: the list gets played if 'animate' is set */
  struct {
    bool animate; /* true if it shall play animation: it will iterate through list of images */
    uint8_t delayCntr; /* delay counter (counting down) to delay animation */
    uint8_t delayCntrReload; /* default 0. Reload value of delayCntr after it reaches zero. */
  } anim; /* used for animations */
  struct {
    int8_t x, y; /* moving deltas */
    uint8_t delayCntr; /* delay counter (counting down) to delay moving */
    uint8_t delayCntrReload; /* default 0. Reload value of delayCntr after it reaches zero. */
  } move; /* used to move a sprite */
  int alive; /* default -1. Used for timed removal of sprite. If positive, it gets counted down to zero. With zero it gets removed */
  int16_t posX, posY; /* current position on screen. Can be negative to support outside screen position */
} Sprite_t;

/*!
 * \brief Create a new sprite object
 * \param images List of images. Can be a single image or a list of images for an animation
 * \param x Initial x position coordinate
 * \param y Initial y position coordinate
 * \return The newly created sprite object, or NULL if failed (no memory)
 */
Sprite_t *Sprite_New(SpriteImage_t *images, McuGDisplaySSD1306_PixelDim x, McuGDisplaySSD1306_PixelDim y);

/*!
 * \brief Releases a sprite object and frees the memory for it, including its images
 * @param sprite The sprite object to be deleted
 */
void Sprite_FreeSprite(Sprite_t *sprite);

/*!
 * \brief Return the number of sprites in a list
 * \param list List to count the elements in it
 * \return Number of sprites in the list
 */
unsigned int Sprite_NofInList(Sprite_t *list);

/*!
 * \brief Used to return a sprite in a list with a given index (order number).
 * \param list List of sprites
 * \param index The index of the sprite to be returned
 * \return Pointer to the sprite or NULL if index does not exist
 */
Sprite_t *Sprite_IndexInList(Sprite_t *list, unsigned int index);

/*!
 * \brief Decides if a sprite is in a list
 * \param list List to search for the sprite
 * \return true if sprite is in list
 */
bool Sprite_IsInList(Sprite_t *sprite, Sprite_t *list);

/*!
 * \brief Add a sprite to a list
 * \param list List where the sprite will be added. Note that this is a reference paramter, as the new sprite could be added at the beginning of the list
 * \param sprite Sprite to be added
 */
void Sprite_AddToList(Sprite_t **list, Sprite_t *sprite);

/*!
 * \brief Remove a sprite from a list and free the memory of it (deletes it)
 * \param list List of Sprites
 * \param sprite The resulting new list (could be empty list or NULL)
 */
void Sprite_DeleteFromList(Sprite_t **list, Sprite_t *sprite);

/*!
 * \brief Removes a sprite from a list, but does not delete it
 * \param list List of sprites
 * \param sprite Sprite to be removed
 */
void Sprite_UnlinkFromList(Sprite_t **list, Sprite_t *sprite);

/*!
 * \brief Deletes a list of sprites and frees the memory
 * \param list List to be deleted
 */
void Sprite_DeleteList(Sprite_t **list);

/*!
 * \brief Moves a sprite, but keeps it within the limits.
 * \param sprite Sprite to be moved
 * \param deltaX Amount of pixels in X direction
 * \param deltaY Amount of pixels in Y direction
 * \param minX Display limit, x minimum (left) coordinate
 * \param maxX Display limit, x maximum (top) coordinate
 * \param minY Display limit, y minimum (top) coordinate
 * \param maxY Display limit, y maximum (bottom) coordinate
 */
void Sprite_MoveLimited(Sprite_t *sprite, int deltaX, int deltaY, McuGDisplaySSD1306_PixelDim minX, McuGDisplaySSD1306_PixelDim maxX, McuGDisplaySSD1306_PixelDim minY, McuGDisplaySSD1306_PixelDim maxY);

/*!
 * \brief Moves a sprite, but keeps it within the display limits.
 * \param sprite Sprite to be moved
 * \param deltaX Amount of pixels in X direction
 * \param deltaY Amount of pixels in Y direction
 */
void Sprite_MoveLimitedDisplay(Sprite_t *sprite, int deltaX, int deltaY);

/*!
 * \brief Decides if a sprite is moving or not
 * \param sprite Pointer to a sprite
 * \return true if the sprite is moving, false otherwise
 */
bool Sprite_IsMoving(Sprite_t *sprite);

/*!
 * \brief Decides if two sprite overlap
 * \param a First sprite
 * \param b Second sprite
 * \return true if they overlap, false otherwise
 */
bool Sprite_Overlap(Sprite_t *a, Sprite_t *b);

/*!
 * Decides if two areas a and b overlap
 * \param ax0 Area a x left coordinate
 * \param ax1 Area a x right coordinate
 * \param ay0 Area a y top coordinate
 * \param ay1 Area a y bottom coordinate
 * \param bx0 Area b x left coordinate
 * \param bx1 Area b x right coordinate
 * \param by0 Area b y top coordinate
 * \param by1 Area b y bottom coordinate
 * \return true if a and b overlap, false otherwise
 */
bool Sprite_OverlappingAreas(int ax0, int ax1, int ay0, int ay1, int bx0, int bx1, int by0, int by1);

/*!
 * \brief Decides if a sprite and a pixel overlap
 * \param sprite Sprite to check
 * \param x Pixel x coordinate
 * \param y Pixel y coordinate
 * \return true if sprite and pixel overlap, false otherwise
 */
bool Sprite_OverlapsWithPixel(Sprite_t *sprite, int x, int y);

/*!
 * \brief Finds a sprite at a given display position
 * \param list List of sprites where to search for a sprite
 * \param x display x position
 * \param y display y position
 * \return The first sprite found at the position
 */
Sprite_t *Sprite_GetSpriteAtPixelPos(Sprite_t *list, int x, int y);

/*!
 * \brief Return the first sprite found in pixel area from a sprite list
 * \param list List of sprites
 * \param x0 X upper left coordinate
 * \param y0 Y upper left coordinate
 * \param x1 X lower right coordinate
 * \param y1 Y lower right coordinate
 * \return first sprite found, NULL otherwise
 */
Sprite_t *Sprite_GetSpriteInPixelAreaFromList(Sprite_t *list, int x0, int y0, int x1, int y1);

/*!
 * \brief Iterator to get one sprite list after each oter
 * \param cntr Counter to iterate through the list. Caller has to initialize it with zero, and it gets incremented for each return
 * \return Pointer to a list pointer
 */
typedef Sprite_t **Sprite_IteratorGetSpriteListFunction(int*cntr);

/*!
 * \brief Return the first sprite found at pixel position, using an iterator to iterate through list of sprites
 * \param x X coordinate
 * \param y Y coordinate
 * \param iteratorFct Function to get one list after each other
 * \return first sprite found, NULL otherwise
 */
Sprite_t *Sprite_GetSpriteAtPixelPosIterated(Sprite_IteratorGetSpriteListFunction iteratorFct, int x, int y);

/*!
 * \brief Return the first sprite found in pixel area, using an iterator to iterate through list of sprites
 * \param x0 X upper left coordinate
 * \param y0 Y upper left coordinate
 * \param x1 X lower right coordinate
 * \param y1 Y lower right coordinate
 * \param iteratorFct Function to get one list after each other
 * \return first sprite found, NULL otherwise
 */
Sprite_t *Sprite_GetSpriteInPixelAreaIterated(Sprite_IteratorGetSpriteListFunction iteratorFct, int x0, int y0, int x1, int y1);

/*!
 * \brief Checks if a sprite (e.g. missile) hits a sprite in a target list (e.g. alien).
 *        If there is a hit, the target (alien) image gets replaced with an animation (e.g. explosion) with a live counter.
 *        So both the sprite and the target remains in the system, but the counter of the target hit sprite will get it removed later.
 * \param sprite The sprite which is aiming at a target
 * \param targetList List of target sprites to go through
 * \param targetHit Pointer to sprite to return, can be NULL. Returns the sprite we have it, or NULL if for no hit.
 * \param boom0 The first image for the boom sequence
 * \param boom1 The second image for the boom sequence
 * \return true if there has been a hit.
 */
bool Sprite_CheckTargetHitBoom(Sprite_t *sprite, Sprite_t **targetList, Sprite_t **targetHit, PIMAGE boom0, PIMAGE boom1);

/*------------------------------------------------------------------------------ */
/* Painting routines */
/*------------------------------------------------------------------------------ */
/*!
 * \item Traverses a list of sprites and increases their age. If a sprite expires, it gets removed from the list. Useful for animations (explosions)
 * \param list List of sprites
 * \return true if list has changed (sprite deleted), false otherwise
 */
bool Sprite_AgeAndCheckIfAlive(Sprite_t **list);

/*!
 * \brief Paints or draws a sprite. Additionally if a sprite is setup for animation, it will advance the animation picture state.
 * \param sprite Sprite to be painted
 */
void Sprite_Paint(Sprite_t *sprite);

/*!
 * \brief Same as Sprite_Paint(), but iterates a list of sprites
 * \param list List of sprites
 */
void Sprite_PaintList(Sprite_t *list);


/*------------------------------------------------------------------------------ */
/* images */
/*------------------------------------------------------------------------------ */
McuGDisplaySSD1306_PixelColor Sprite_GetPImageMonoBitmapPixel(PIMAGE image, uint16_t x, uint16_t y);
void Sprite_SetPImageMonoBitmapPixel(PIMAGE image, uint16_t x, uint16_t y);
void Sprite_ClearPImageMonoBitmapPixel(PIMAGE image, uint16_t x, uint16_t y);

/*!
 * \brief Creates a new data structure for an image and initializes the image with zero bits.
 * \param width Width of the image in pixels, must be greater than zero
 * \param height Height of the image in pixels, must be greater than zero
 * \return The pointer to the TIMAGE structure
 */
PIMAGE Sprite_NewEmptyPImage(uint16_t width, uint16_t height);

/*!
 * \brief Create a new sprite image from a PIMAGE in ROM
 * \param image Image data to be used
 * \return Pointer to sprite image or NULL if failed (no memory)
 */
SpriteImage_t *Sprite_NewImageFromROM(const PIMAGE image);

/*!
 * \brief Create a new sprite image from a PIMAGE in RAM
 * \param image Image data to be used
 * \return Pointer to sprite image or NULL if failed (no memory)
 */
SpriteImage_t *Sprite_NewImageFromRAM(const PIMAGE image);

/*!
 * \brief Ad a sprite image to a list of sprite images
 * @param list
 * @param image
 */
void Sprite_ImageAddToList(SpriteImage_t **list, SpriteImage_t *image);

/*!
 * \brief Iterate through list of sprites in spriteList and check if it hits any of the target list.
 *        If yes, update the target hit and remove the missile.
 *        If an target has a hit, it will add an explosion animation to it. For the shields it will weaken it.
 * \param spriteList List of sprites which are checked against the target list
 * \param removSprite If set to true, the sprite which hit the target gets removed
 * \param targetList List of sprites which are the targets. If hit, they get replaced with a boom animation
 * \param points Number of points for a hit
 * \pram hitCallback Callback which gets called in case of collision
 * \param boom0 First image for explosion
 * \param boom1 Second image for explosion
 * \return true if we need a display update because something has changed
 */
bool Sprite_CheckCollision(Sprite_t **spriteList, bool removeSprite, Sprite_t **targetList, int32_t points, void (*hitCallback)(Sprite_t *aimer, Sprite_t *target), const PIMAGE boom0, const PIMAGE boom1);

/*!
 * \brief Delete a list of sprite images
 * \param list List to be deleted
 */
void Sprite_ImageDeleteList(SpriteImage_t **list);

/*!
 * \brief Module de-initialization
 */
void Sprite_Deinit(void);

/*!
 * \brief Module initialization
 */
void Sprite_Init(void);


#endif /* SPRITE_H_ */
