#include "../include/button.h"

#ifndef __VSTACK_H__
#define __VSTACK_H__

enum ALIGNMENT {LEADING, CENTER, TRAILING};

typedef struct {
  int origin_x;
  int origin_y;
  int curr_y;
  int curr_x;
  int x_pad;
  int y_pad;
  int width;
  int height;
  enum ALIGNMENT alignment;
} vstack_t;

vstack_t vstack(int ox, int oy, int x_pad, int y_pad, enum ALIGNMENT alignment); // this one returns vstack_wh but passes in 1920x1080 by default
vstack_t vstack_wh(int ox, int oy, int x_pad, int y_pad, int screen_width, int screen_height, enum ALIGNMENT alignment);
button_t stack_add_button(vstack_t*, SDL_Renderer*, int, int, int, int, int, char*, TTF_Font*);

#endif
