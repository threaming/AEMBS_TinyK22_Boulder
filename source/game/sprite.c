/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sprite.h"
#include "McuRTOS.h"
#include <assert.h>
#include <string.h> /* for memcpy() */
#include "game/score.h"
#include "game/game.h"

#define SPRITE_USE_HEAP_MONITOR   (0 && configUSE_SEGGER_SYSTEM_VIEWER_HOOKS)

#if SPRITE_USE_HEAP_MONITOR
typedef enum SYSVIEW_HeapTag_e {
  SYSVIEW_HEAP_TAG_TIMAGE,
  SYSVIEW_HEAP_TAG_IMAGE,
  SYSVIEW_HEAP_TAG_PIXELS,
  SYSVIEW_HEAP_TAG_SPRITE,
  SYSVIEW_HEAP_TAG_SPRITE_IMAGE,
} SYSVIEW_HeapTag_e;
#endif

void Sprite_ImageDeleteList(SpriteImage_t **list);

unsigned int Sprite_NofInList(Sprite_t *list) {
  unsigned int nof = 0;

  while(list!=NULL) {
    nof++;
    list = list->next;
  }
  return nof;
}

Sprite_t *Sprite_IndexInList(Sprite_t *list, unsigned int index) {
  Sprite_t *sprite;
  int i;

  sprite = list;
  i = 0;
  for (;;) {
    if (sprite==NULL) {
      return NULL; /* end of list, index not found */
    }
    if (i==index) {
      return sprite;
    }
    sprite = sprite->next;
    i++;
  }
}

bool Sprite_IsInList(Sprite_t *sprite, Sprite_t *list) {
  while(list!=NULL) {
    if (sprite==list) { /* found */
      return true;
    }
    list = list->next;
  }
  return false;
}

static McuGDisplaySSD1306_PixelDim LimitPosition(int pos, McuGDisplaySSD1306_PixelDim min, McuGDisplaySSD1306_PixelDim max) {
  if (pos<min) {
    return min;
  }
  if (pos>max) {
    return max;
  }
  return pos;
}

void Sprite_MoveLimited(Sprite_t *sprite, int deltaX, int deltaY, McuGDisplaySSD1306_PixelDim minX, McuGDisplaySSD1306_PixelDim maxX, McuGDisplaySSD1306_PixelDim minY, McuGDisplaySSD1306_PixelDim maxY) {
  if (sprite!=NULL) {
    sprite->posX = LimitPosition((int)sprite->posX + deltaX, minX, maxX-sprite->images->image->width);
    sprite->posY = LimitPosition((int)sprite->posY + deltaY, minY, maxY-sprite->images->image->height);
  }
}

void Sprite_MoveLimitedDisplay(Sprite_t *sprite, int deltaX, int deltaY) {
  Sprite_MoveLimited(sprite, deltaX, deltaY, 0, McuGDisplaySSD1306_GetWidth(), 0, McuGDisplaySSD1306_GetHeight());
}

bool Sprite_IsMoving(Sprite_t *sprite) {
  return sprite->move.x!=0 || sprite->move.y!=0;
}

bool Sprite_OverlappingAreas(int ax0, int ax1, int ay0, int ay1, int bx0, int bx1, int by0, int by1) {
  /* see https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other */
   /* (x0,y0) are the left upper coordinate, (x1,y1) are lower right coordinates.
   * (0,0) is top left display coordinate, with x increasing to the right and y increasing to the bottom
   */

  /* *no* overlap exists, if
   *  (a) Left_Edge_A > Right_Edge_B (A is totally right of B)
   * or
   *  (b) Right_Edge_A < Left_Edge_B (A is totally left of B)
   * or
   *  (c) Top_A > Bottom_B (A is totally below B)
   * or
   *  (d) Bottom_A < Top_B (A is totally above B)
   *
   *  Therefore no overlap:  a || b || c || d
   *  or *overlap* is: !(a || b || c || d)  => De Morgans's law => !a && !b && !c && !d
   */
  return ax0<=bx1 && ax1>=bx0 && ay0<=by1 && ay1>=by0;
}

bool Sprite_OverlapsWithPixel(Sprite_t *sprite, int x, int y) {
  int ax0, ax1, ay0, ay1;
  int bx0, bx1, by0, by1;

  ax0 = sprite->posX;
  ax1 = sprite->posX + sprite->images->image->width-1;
  ay0 = sprite->posY;
  ay1 = sprite->posY + sprite->images->image->height-1;

  bx0 = x;
  bx1 = x;
  by0 = y;
  by1 = y;

  return Sprite_OverlappingAreas(ax0, ax1, ay0, ay1, bx0, bx1, by0, by1);
}

bool Sprite_Overlap(Sprite_t *a, Sprite_t *b) {
  /* see https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other */
  int ax0, ax1, ay0, ay1;
  int bx0, bx1, by0, by1;
  /* (x0,y0) are the left upper coordinate, (x1,y1) are lower right coordinates.
   * (0,0) is top left display coordinate, with x increasing to the right and y increasing to the bottom
   * */
  ax0 = a->posX;
  ax1 = a->posX + a->images->image->width-1;
  ay0 = a->posY;
  ay1 = a->posY + a->images->image->height-1;

  bx0 = b->posX;
  bx1 = b->posX + b->images->image->width-1;
  by0 = b->posY;
  by1 = b->posY + b->images->image->height-1;

  return Sprite_OverlappingAreas(ax0, ax1, ay0, ay1, bx0, bx1, by0, by1);
}

McuGDisplaySSD1306_PixelColor Sprite_GetPImageMonoBitmapPixel(PIMAGE image, uint16_t x, uint16_t y) {
  uint8_t data;
  McuGDisplaySSD1306_PixelColor pixel;
  int i;

  data = image->pixmap[(y*(((image->width-1)/8)+1)) + (x/8)];
  i = 7-(x%8); /* pixel order is from MSB to LSB */
  pixel = (McuGDisplaySSD1306_PixelColor)((data&(1<<i))>>i); /* extract pixel out of bitstream */
  return pixel;
}

void Sprite_SetPImageMonoBitmapPixel(PIMAGE image, uint16_t x, uint16_t y) {
  uint8_t *dataP;
  int i;

  dataP = (uint8_t*)&image->pixmap[(y*(((image->width-1)/8)+1)) + (x/8)];
  i = 7-(x%8); /* pixel order is from MSB to LSB */
  *dataP |= (1<<i); /* set pixel in bitstream */
}

void Sprite_ClearPImageMonoBitmapPixel(PIMAGE image, uint16_t x, uint16_t y) {
  uint8_t *dataP;
  int i;

  dataP = (uint8_t*)&image->pixmap[(y*(((image->width-1)/8)+1)) + (x/8)];
  i = 7-(x%8); /* pixel order is from MSB to LSB */
  *dataP &= ~(1<<i); /* clear pixel in bitstream */
}


PIMAGE Sprite_NewEmptyPImage(uint16_t width, uint16_t height) {
  TIMAGE *p;

  assert(width>0 && height>0);
#if SPRITE_USE_HEAP_MONITOR
  p = pvPortMallocExt(sizeof(TIMAGE), SYSVIEW_HEAP_TAG_TIMAGE);
#else
  p = pvPortMalloc(sizeof(TIMAGE));
#endif
  assert(p!=NULL);
  p->name = NULL; /* don't care */
  p->height = height;
  p->width = width;
  p->size = (((width-1)/8)+1) * height; /* align width to 8bits */
#if SPRITE_USE_HEAP_MONITOR
  p->pixmap = pvPortMallocExt(p->size, SYSVIEW_HEAP_TAG_PIXELS);
#else
  p->pixmap = pvPortMalloc(p->size);
#endif
  memset((void*)p->pixmap, 0, p->size);
  return p;
}

SpriteImage_t *Sprite_NewImageFromROM(const PIMAGE image) {
  SpriteImage_t *p;
  PIMAGE i;

  /* create new sprite image */
#if SPRITE_USE_HEAP_MONITOR
  p = pvPortMallocExt(sizeof(SpriteImage_t), SYSVIEW_HEAP_TAG_SPRITE_IMAGE);
#else
  p = pvPortMalloc(sizeof(SpriteImage_t));
#endif
  assert(p!=NULL);
  /* create the image in RAM. PIMAGE is pointing to ROM data */
#if SPRITE_USE_HEAP_MONITOR
  i = pvPortMallocExt(sizeof(TIMAGE), SYSVIEW_HEAP_TAG_TIMAGE);
#else
  i = pvPortMalloc(sizeof(TIMAGE));
#endif
  assert(i!=NULL);
#if SPRITE_USE_HEAP_MONITOR
  i->pixmap = pvPortMallocExt(image->size, SYSVIEW_HEAP_TAG_IMAGE);
#else
  i->pixmap = pvPortMalloc(image->size);
#endif
  assert(i->pixmap!=NULL);
  memcpy((void*)i->pixmap, image->pixmap, image->size);
  i->size = image->size;
  i->height = image->height;
  i->width = image->width;
  i->name = NULL; /* don't care */
  p->image = i;
  p->next = p; /* circular */
  p->prev = p; /* circular */
  return p;
}

SpriteImage_t *Sprite_NewImageFromRAM(PIMAGE image) {
  SpriteImage_t *p;

  /* create new sprite image */
#if SPRITE_USE_HEAP_MONITOR
  p = pvPortMallocExt(sizeof(SpriteImage_t), SYSVIEW_HEAP_TAG_SPRITE_IMAGE);
#else
  p = pvPortMalloc(sizeof(SpriteImage_t));
#endif
  assert(p!=NULL);
  p->image = image;
  p->next = p; /* circular */
  p->prev = p; /* circular */
  return p;
}


Sprite_t *Sprite_New(SpriteImage_t *images, McuGDisplaySSD1306_PixelDim x, McuGDisplaySSD1306_PixelDim y) {
  Sprite_t *p;
#if SPRITE_USE_HEAP_MONITOR
  p = pvPortMallocExt(sizeof(Sprite_t), SYSVIEW_HEAP_TAG_SPRITE);
#else
  p = pvPortMalloc(sizeof(Sprite_t));
#endif
  assert(p!=NULL);
  p->images = images;
  p->anim.animate = false; /* by default, no animation */
  p->anim.delayCntr = p->anim.delayCntrReload = 0; /* no animation delay */
  p->move.x = p->move.y = 0; /* not moving */
  p->move.delayCntr = p->move.delayCntrReload = 0; /* no moving delay */
  p->alive = -1; /* positive: counts down, zero: delete sprite */
  p->posX = x;
  p->posY = y;
  p->prev = p->next = NULL;
  return p;
}

void Sprite_FreeImage(SpriteImage_t *image) {
  if (image!=NULL) {
    vPortFree((void*)image->image->pixmap);
    image->image->pixmap = NULL;
    vPortFree(image->image);
    image->image = NULL;
    vPortFree(image);
  }
}

void Sprite_FreeSprite(Sprite_t *sprite) {
  if (sprite!=NULL) {
    Sprite_ImageDeleteList(&sprite->images);
    vPortFree(sprite);
  }
}

void Sprite_AddToList(Sprite_t **list, Sprite_t *sprite) {
  if (*list==NULL) { /* empty list */
    *list = sprite;
  } else { /* insert in front */
    sprite->next = *list;
    sprite->prev = NULL;
    (*list)->prev = sprite;
    *list = sprite;
  }
}

void Sprite_ImageAddToList(SpriteImage_t **list, SpriteImage_t *image) {
  if (*list==NULL) { /* empty list: add to it (element is circular) */
    *list = image;
    image->next = image;
    image->prev = image;
  } else { /* insert in front, update circular list */
    (*list)->prev->next = image;
    image->next = *list;
    image->prev = (*list)->prev;
    (*list)->prev = image;
    *list = image;
  }
}

void Sprite_UnlinkFromList(Sprite_t **list, Sprite_t *sprite) {
  if (*list==sprite) { /* remove from front of list */
    if (sprite->next!=NULL) {
      sprite->next->prev = NULL;
    }
    *list = sprite->next;
  } else { /* unlink */
    if (sprite->next != NULL) {
      sprite->next->prev = sprite->prev;
    }
    if (sprite->prev!=NULL) {
      sprite->prev->next = sprite->next;
    }
  }
  sprite->next = NULL;
  sprite->prev = NULL;
}

void Sprite_DeleteFromList(Sprite_t **list, Sprite_t *sprite) {
  Sprite_UnlinkFromList(list, sprite);
  Sprite_FreeSprite(sprite);
}

void Sprite_ImageDeleteFromList(SpriteImage_t **list, SpriteImage_t *image) {
  if (image==NULL || list==NULL || *list==NULL) {
    return;
  }
  if (*list==image && (*list)->next==image) { /* only element in list? */
    *list = NULL; /* empty list */
  } else if (*list==image) { /* unlink and update pointer to list */
    *list = image->next; /* point to next element */
    image->next->prev = image->prev;
    image->prev->next = image->next;
  } else { /* unlink only */
    image->next->prev = image->prev;
    image->prev->next = image->next;
  }
  image->next = NULL;
  image->prev = NULL;
  Sprite_FreeImage(image);
}

void Sprite_DeleteList(Sprite_t **list) {
  if (list==NULL) {
    return;
  }
  while(*list!=NULL) {
    Sprite_DeleteFromList(list, *list);
  }
}

void Sprite_ImageDeleteList(SpriteImage_t **list) {
  if (list==NULL) {
    return;
  }
  while(*list!=NULL) {
    Sprite_ImageDeleteFromList(list, *list);
  }
}

Sprite_t *Sprite_GetSpriteAtPixelPosIterated(Sprite_IteratorGetSpriteListFunction iteratorFct, int x, int y) {
  int cntr = 0;
  Sprite_t **sprites;
  Sprite_t *sprite;

  do {
    sprites = iteratorFct(&cntr);
    if (sprites!=NULL) {
      sprite = Sprite_GetSpriteAtPixelPos(*sprites, x, y);
      if (sprite!=NULL) {
        return sprite;
      }
    }
  } while(cntr!=0);
  return NULL;
}

Sprite_t *Sprite_GetSpriteAtPixelPos(Sprite_t *list, int x, int y) {
  Sprite_t *sprite;

  sprite = list;
  while(sprite!=NULL) {
    if (Sprite_OverlapsWithPixel(sprite, x, y)) {
      return sprite;
    }
    sprite = sprite->next;
  }
  return sprite;
}

Sprite_t *Sprite_GetSpriteInPixelAreaFromList(Sprite_t *list, int x0, int y0, int x1, int y1) {
  Sprite_t *sprite;

  sprite = list;
  while (sprite!=NULL) {
    if (Sprite_OverlappingAreas(x0, x1, y0, y1,
        sprite->posX,
        sprite->posX+sprite->images->image->width-1,
        sprite->posY,
        sprite->posY+sprite->images->image->height-1)
       )
    {
      return sprite;
    }
    sprite = sprite->next;
  }
  return NULL;
}

Sprite_t *Sprite_GetSpriteInPixelAreaIterated(Sprite_IteratorGetSpriteListFunction iteratorFct, int x0, int y0, int x1, int y1) {
  int cntr = 0;
  Sprite_t **sprites;
  Sprite_t *sprite;

  do {
    sprites = iteratorFct(&cntr);
    if (sprites!=NULL) {
      sprite = Sprite_GetSpriteInPixelAreaFromList(*sprites, x0, y0, x1, y1);
      if (sprite!=NULL) { /* found one */
        return sprite;
      }
    }
  } while(cntr!=0);
  return NULL;
}

bool Sprite_CheckTargetHitBoom(Sprite_t *sprite, Sprite_t **targetList, Sprite_t **targetHit, const PIMAGE boom0, const PIMAGE boom1) {
  Sprite_t *target;
  SpriteImage_t *boom;
  int centerX, centerY;

  if (targetHit!=NULL) {
    *targetHit = NULL; /* initialize */
  }
  /* check if we have hit a sprite */
  target = *targetList;
  while (target!=NULL) { /* check all targets, if we have hit one of them */
    if (target->alive<0 && Sprite_Overlap(sprite, target)) { /* hit a target? */
      /* remember old object center position */
      centerX = target->posX + target->images->image->width/2;
      centerY = target->posY + target->images->image->height/2;
      /* remove existing images */
      Sprite_ImageDeleteList(&target->images);
      /* add two 'boom' images */
      boom = Sprite_NewImageFromROM(boom1);
      Sprite_ImageAddToList(&target->images, boom);
      boom = Sprite_NewImageFromROM(boom0);
      Sprite_ImageAddToList(&target->images, boom);
      target->alive = 3; /* counter for explosion */
      target->move.x = target->move.y = 0; /* stop moving */
      target->posX = centerX - target->images->image->width/2; /* center boom image */
      target->posY = centerY - target->images->image->height/2; /* center boom image */
      if (targetHit!=NULL) {
        *targetHit = target; /* report what we have hit */
      }
      return true; /* yes, we have hit one */
    }
    target = target->next;
  } /* all targets */
  return false; /* no target hit */
}


bool Sprite_AgeAndCheckIfAlive(Sprite_t **list) {
  bool changed = false;
  Sprite_t *sprite, *next;

  if (list==NULL) {
    return false;
  }
  /* check if ship missiles have hit an alien */
  sprite = *list;
  while (sprite!=NULL) { /* check all aliens */
    next = sprite->next;
    if (sprite->alive==0) { /* life expired? */
      Sprite_DeleteFromList(list, sprite); /* remove from list */
      changed = true;
    } else if (sprite->alive>0) {
      sprite->alive--;
      changed = true;
    }
    sprite = next;
  } /* while */
  return changed;
}

bool Sprite_CheckCollision(Sprite_t **spriteList, bool removeSprite, Sprite_t **targetList, int32_t points, void (*hitCallback)(Sprite_t *aimer, Sprite_t *target), const PIMAGE boom0, const PIMAGE boom1) {
  bool changed = false;
  Sprite_t *sprite, *next, *newList = NULL;
  Sprite_t *targetHit;

  /* check if a sprite from the spriteList has hit a target from the targetList */
  sprite = *spriteList;
  while (sprite!=NULL) { /* iterate list */
    next = sprite->next;
    Sprite_UnlinkFromList(spriteList, sprite); /* remove current sprite from list, because the sprite can be in the target list too */
    if (Sprite_CheckTargetHitBoom(sprite, targetList, &targetHit, boom0, boom1)) {
      if (hitCallback!=NULL) {
        hitCallback(sprite, targetHit);
      }
      if(points!=0){	// some points received
    	  Game_ScoreEvent(points);
      }
      Score_AddGameScore(points);
      if (removeSprite) {
        Sprite_FreeSprite(sprite); /* delete and free memory */
      } else {
        Sprite_AddToList(&newList, sprite); /* add to temporary list */
      }
      changed |= true;
    } else { /* no hit: add sprite to temporary list */
      Sprite_AddToList(&newList, sprite); /* add to temporary list */
    }
    sprite = next; /* next in list */
  } /* while */
  *spriteList = newList;
  return changed;
}

void Sprite_Paint(Sprite_t *sprite) {
  if (sprite==NULL) {
    return;
  }
  if (sprite->images!=NULL) {
    McuGDisplaySSD1306_DrawMonoBitmap(sprite->posX, sprite->posY, sprite->images->image, McuGDisplaySSD1306_COLOR_WHITE, McuGDisplaySSD1306_COLOR_BLACK);

    /* update animation for next iteration */
    if (sprite->anim.animate) {
      if (sprite->anim.delayCntrReload != 0) { /* have a delay? */
        if (sprite->anim.delayCntr==0) { /* expired: reload and paint */
          sprite->anim.delayCntr = sprite->anim.delayCntrReload;
          sprite->images = sprite->images->next; /* go to next image for next iteration */
        } else if (sprite->anim.delayCntr>0) { /* still counting down */
          sprite->anim.delayCntr--;
        }
      }
    }
  } /* if animate */

  /* update position for next iteration */
  if (Sprite_IsMoving(sprite)) { /* move it? */
    if (sprite->move.delayCntr==0) { /* expired or no delay? */
  #if 0 /* keep sprite within display */
      Sprite_MoveLimitedDisplay(sprite, sprite->move.x, sprite->move.y);
  #else /* allow sprite to move outside of display */
      sprite->posX += sprite->move.x;
      sprite->posY += sprite->move.y;
  #endif
      if (sprite->move.delayCntrReload != 0) { /* restart counter? */
        sprite->move.delayCntr = sprite->move.delayCntrReload;
      }
    } else if (sprite->move.delayCntr>0) { /* count down? */
      sprite->move.delayCntr--;
    }
  } /* if move */
}

void Sprite_PaintList(Sprite_t *list) {
  Sprite_t *sprite = list;

  while(sprite!=NULL) {
    Sprite_Paint(sprite);
    sprite = sprite->next;
  }
}

void Sprite_Deinit(void) {
  /* nothing needed */
}

void Sprite_Init(void) {
  /* nothing needed */
}
