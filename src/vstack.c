#include <stdio.h>
#include <stdlib.h>

#include "../include/vstack.h"
#include "../include/button.h"

vstack_t vstack(int ox, int oy, int x_pad, int y_pad) {
  return vstack_wh(ox, oy, x_pad, y_pad, 1920, 1080);
}

vstack_t vstack_wh(int ox, int oy, int x_pad, int y_pad, int screen_width, int screen_height) {
  vstack_t vstack;
  vstack.origin_x = ox;
  vstack.origin_y = oy;
  vstack.x_pad = x_pad;
  vstack.y_pad = y_pad;

  vstack.curr_x = x_pad;
  vstack.curr_y = y_pad;

  vstack.screen_width = screen_width;
  vstack.screen_height = screen_height;
  return vstack;
}

button_t stack_add_button(vstack_t* stack, int w, int h, int r, int g, int b, char* title) {
  int x = stack->origin_x + stack->curr_x;
  int y = stack->origin_y + stack->curr_y;
  button_t btn = button(x, y, w, h, r, g, b, title);

  stack->curr_y = stack->curr_y + ((stack->y_pad * 2) + h);

  return btn;
}
