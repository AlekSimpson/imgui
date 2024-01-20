#include "color.h"
#include <SDL2/SDL.h>

#ifndef __LABEL_H__
#define __LABEL_H__

// TODO: not sure if this is the most optimal order for the attributes (not sure about any of the structs attribute orders lol)
typedef struct {
  char* text;
  SDL_Rect rect;
  color_t fg_color;
} label_t;

void render_label(SDL_Renderer*, label_t*);
label_t label(char*, int x, int y, int w, int h, int r, int g, int b);

#endif
