#include <stdio.h>
#include <stdlib.h>

#include "../include/vstack.h"
#include "../include/button.h"

vstack_t vstack(int ox, int oy, int x_pad, int y_pad, enum ALIGNMENT alignment) {
  return vstack_wh(ox, oy, x_pad, y_pad, 1920, 1080, alignment);
}

vstack_t vstack_wh(int ox, int oy, int x_pad, int y_pad, int width, int height, enum ALIGNMENT alignment) {
  vstack_t vstack;
  vstack.origin_x = ox;
  vstack.origin_y = oy;
  vstack.x_pad = x_pad;
  vstack.y_pad = y_pad;

  vstack.curr_x = x_pad;
  vstack.curr_y = y_pad;

  vstack.width = width;
  vstack.height = height;

  vstack.alignment = alignment;
  return vstack;
}

button_t stack_add_button(vstack_t* stack, SDL_Renderer* ren, int w, int h, int r, int g, int b, char* title, TTF_Font* font) {
  enum ALIGNMENT alignment = stack->alignment;
  int x, y;
  button_t btn;

  if (w > stack->width || h > stack->height) {
    return btn;
  }

  switch (alignment) {
    case LEADING:
      x = (stack->origin_x + stack->curr_x);
      break;
    case CENTER:
      x = ((stack->width / 2) - (w / 2));
      break;
    case TRAILING:
      x = (stack->origin_x + stack->width) - (w + stack->curr_x);
      break;
  }

  y = stack->origin_y + stack->curr_y;
  btn = button(ren, x, y, w, h, r, g, b, title, font);
  stack->curr_y = stack->curr_y + ((stack->y_pad * 2) + h);

  return btn;
}
