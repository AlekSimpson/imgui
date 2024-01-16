#include "color.h"
#include <SDL2/SDL.h>

#ifndef __LABEL_H__
#define __LABEL_H__

typedef struct {
  char* text;
  color_t fg_color;
  SDL_Rect* rect;
} label_t;

void render_label(SDL_Renderer*, label_t*);
label_t label(char*, color_t*, SDL_Rect*);

#endif
