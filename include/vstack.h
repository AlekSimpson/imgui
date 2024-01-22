#include "../include/button.h"

#ifndef __VSTACK_H__
#define __VSTACK_H__

typedef struct {
  int origin_x;
  int origin_y;
  int curr_y;
  int curr_x;
  int x_pad;
  int y_pad;
  int screen_width;
  int screen_height;
} vstack_t;

vstack_t vstack(int ox, int oy, int x_pad, int y_pad); // this one returns vstack_wh but passes in 1920x1080 by default
vstack_t vstack_wh(int ox, int oy, int x_pad, int y_pad, int screen_width, int screen_height);
// void stack_add(vstack_t*, button_t*);
button_t stack_add_button(vstack_t*, int, int, int, int, int, char*);

#endif
