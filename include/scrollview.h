#include <stdbool.h>

#include "button.h"
#include "color.h"

#ifndef __SCROLLVIEW_H__
#define __SCROLLVIEW_H__

typedef struct {
  int id;
  int* ID_STATE;

  int origin_x;
  int origin_y;

  int width;
  int height;

  int x_pad;
  int pad_between; // scroll views do not have initial padding unlike stacks
  int max_height;
  int min_height;

  int scroll_y;
  int curr_y;

  // this is to check if the list should even be able to scroll (if for example there are only 1 or 2 elements and the elements do not take up the full space of the scroll box yet) 
  bool list_does_overflow; 
  bool is_active;
  color_t color;
} scrollview_t;

scrollview_t scrollview(int* id_state, int ox, int oy, int x_pad, int pad_between, int width, int height, bool ldo);
scrollview_t scrollview_color(int* id_state, int ox, int oy, int x_pad, int pad_between, int width, int height, bool ldo, color_t color);
void scrollview_update(scrollview_t* sv);

button_t scrollview_add_button(scrollview_t* sv, SDL_Renderer* ren, int w, int h, int r, int g, int b, char* title, TTF_Font* font);
button_t scrollview_add_button_color(scrollview_t* sv, SDL_Renderer* ren, int w, int h, color_t* color, char* title, TTF_Font* font);

#endif
