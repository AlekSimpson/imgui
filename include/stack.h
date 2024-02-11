#include "../include/button.h"
#include "../include/label.h"

#ifndef __VSTACK_H__
#define __VSTACK_H__

enum VALIGNMENT { LEADING, CENTER, TRAILING };
enum HALIGNMENT { TOP, MIDDLE, BOTTOM };

typedef struct {
  int origin_x;
  int origin_y;

  int curr_y;

  int pad_init;
  int pad_between;
  int x_pad;

  int width;
  int height;

  enum VALIGNMENT valignment;
} vstack_t;

typedef struct {
  int origin_x;
  int origin_y;

  int curr_x;

  int pad_init;
  int pad_between;
  int y_pad;

  int width;
  int height;

  enum HALIGNMENT halignment;
} hstack_t;

vstack_t vstack(int ox, int oy, int x_pad, int y_pad, int pad_between, enum VALIGNMENT alignment); // this one returns vstack_wh but passes in 1920x1080 by default
vstack_t vstack_wh(int ox, int oy, int x_pad, int y_pad, int pad_between, int screen_width, int screen_height, enum VALIGNMENT alignment);
button_t vstack_add_button(vstack_t*, SDL_Renderer*, int, int, int, int, int, char*, TTF_Font*);
hstack_t vstack_add_hstack(vstack_t*, int x_pad, int y_pad, int pad_between, int w, int h, enum HALIGNMENT alignment);
vstack_t vstack_add_vstack(vstack_t*, int x_pad, int y_pad, int pad_between, int w, int h, enum VALIGNMENT alignment);
label_t  vstack_add_label(vstack_t*, SDL_Renderer*, TTF_Font*, char*, int w, int h, int r, int g, int b);

int calculateVAlignment(int ox, int cx, int w, int item_w, enum VALIGNMENT valignment);
int calculateHAlignment(int oy, int cy, int h, int item_h, enum HALIGNMENT halignment);

hstack_t hstack(int ox, int oy, int x_pad, int y_pad, int pad_between, enum HALIGNMENT alignment); // this one returns vstack_wh but passes in 1920x1080 by default
hstack_t hstack_wh(int ox, int oy, int x_pad, int y_pad, int pad_between, int screen_width, int screen_height, enum HALIGNMENT alignment);
button_t hstack_add_button(hstack_t*, SDL_Renderer*, int, int, int, int, int, char*, TTF_Font*);
hstack_t hstack_add_hstack(hstack_t*, int x_pad, int y_pad, int pad_between, int w, int h, enum HALIGNMENT alignment);
vstack_t hstack_add_vstack(hstack_t*, int x_pad, int y_pad, int pad_between, int w, int h, enum VALIGNMENT alignment);
label_t  hstack_add_label(hstack_t*, SDL_Renderer*, TTF_Font*, char*, int w, int h, int r, int g, int b);

#endif
