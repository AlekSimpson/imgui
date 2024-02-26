#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"
#include "../include/button.h"
#include "../include/scrollview.h"

int calculateVAlignment(int ox, int cx, int w, int item_w, enum VALIGNMENT valignment) {
  // cx used to be for "curr_x", curr_x was removed from vstack_t and instead x_pad is used for cx 
  switch (valignment) {
    case LEADING:
      return (ox + cx);
    case CENTER:
      return ((w / 2) - (item_w / 2));
    case TRAILING:
      return (ox + w) - (item_w + cx);
    default:
      return (ox + cx);
  }
}

int calculateHAlignment(int oy, int cy, int h, int item_h, enum HALIGNMENT halignment) {
  switch (halignment) {
    case TOP:
      return (oy + cy);
    case CENTER:
      return oy + ((h / 2) - (item_h / 2));
    case BOTTOM:
      return (oy + h) - (item_h + cy);
    default:
      return (oy + cy);
  }
}

vstack_t vstack(int ox, int oy, int x_pad, int pad_init, int pad_between, enum VALIGNMENT alignment) {
  return vstack_wh(ox, oy, x_pad, pad_init, pad_between, 1920, 1080, alignment);
}

vstack_t vstack_wh(int ox, int oy, int x_pad, int pad_init, int pad_between, int width, int height, enum VALIGNMENT alignment) {
  vstack_t vstack;
  vstack.origin_x = ox;
  vstack.origin_y = oy;

  vstack.pad_init = pad_init;
  vstack.pad_between = pad_between;
  vstack.x_pad = x_pad; // curr_x

  // keep track of next position for next item in the stack
  vstack.curr_y = pad_init;

  vstack.width = width;
  vstack.height = height;

  vstack.valignment = alignment;
  return vstack;
}

// stack_pointer: (curr_y/curr_x) - (stack height/stack width)
bool item_exceeds_stack_size(int sw, int sh, int w, int h, int stack_pointer) {
  return (w > sw || h > sh || stack_pointer >= 0);
}

button_t vstack_add_button(vstack_t* stack, SDL_Renderer* ren, int w, int h, int r, int g, int b, char* title, TTF_Font* font) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_y - stack->height))) {
    printf("EXCEPTION: button to big for vstack\n");
    exit(1);
  }

  enum VALIGNMENT valignment = stack->valignment;
  int btn_x, btn_y;
  button_t btn;

  btn_x = calculateVAlignment(stack->origin_x, stack->x_pad, stack->width, w, valignment);
  btn_y = stack->origin_y + stack->curr_y;
  btn = button(ren, btn_x, btn_y, w, h, r, g, b, title, font);
  stack->curr_y = stack->curr_y + (h + stack->pad_between);
  return btn;
}

vstack_t vstack_add_vstack(vstack_t* stack, int x_pad, int pad_init, int pad_between, int w, int h, enum VALIGNMENT valignment) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_y - stack->height))) {
    printf("EXCEPTION: vstack to big for vstack\n");
    exit(1);
  }

  enum VALIGNMENT stack_valignment = stack->valignment;
  int stk_x, stk_y;
  vstack_t new_stack;

  stk_x = calculateVAlignment(stack->origin_x, stack->x_pad, stack->width, w, stack_valignment);
  stk_y = stack->origin_y+stack->curr_y;
  new_stack = vstack_wh(stk_x, stk_y, x_pad, pad_init, pad_between, w, h, valignment);
  stack->curr_y = stack->curr_y + (h + stack->pad_between);
  return new_stack;
}

hstack_t vstack_add_hstack(vstack_t* stack, int x_pad, int pad_init, int pad_between, int w, int h, enum HALIGNMENT halignment) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_y - stack->height))) {
    printf("EXCEPTION: hstack to big for vstack\n");
    exit(1);
  }

  enum VALIGNMENT stack_valignment = stack->valignment;
  int stk_x, stk_y;
  hstack_t new_stack;

  stk_x = calculateVAlignment(stack->origin_x, stack->x_pad, stack->width, w, stack_valignment);
  stk_y = stack->origin_y + stack->curr_y;
  new_stack = hstack_wh(stk_x, stk_y, x_pad, pad_init, pad_between, w, h, halignment);
  stack->curr_y = stack->curr_y + (h + stack->pad_between);
  return new_stack;
}

label_t vstack_add_label(vstack_t* stack, SDL_Renderer* ren, TTF_Font* font, char* title, int w, int h, int r, int g, int b) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_y - stack->height))) {
    printf("EXCEPTION: label to big for vstack\n");
    exit(1);
  }

  enum VALIGNMENT valignment = stack->valignment;
  int lbl_x, lbl_y;
  label_t lbl;

  lbl_x = calculateVAlignment(stack->origin_x, stack->x_pad, stack->width, w, valignment);
  lbl_y = stack->origin_y + stack->curr_y;
  lbl = label(ren, font, title, lbl_x, lbl_y, w, h, r, g, b);
  stack->curr_y = stack->curr_y + (h + stack->pad_between);
  return lbl;
}

// cannot return direct type, instead returns type inside of a union with other special view types
special_view_u vstack_add_scrollview(vstack_t* stack, int* id_state, int x_pad, int pad_between, int width, int height) {
  if (item_exceeds_stack_size(stack->width, stack->height, width, height, (stack->curr_y - stack->height))) {
    printf("EXCEPTION: scroll view to big for vstack\n");
    exit(1);
  }

  enum VALIGNMENT valignment = stack->valignment;
  int sv_x, sv_y;
  scrollview_t sv;
  special_view_u svu;

  sv_x = calculateVAlignment(stack->origin_x, stack->x_pad, stack->width, width, valignment);
  sv_y = stack->origin_y + stack->curr_y;
  sv = scrollview(id_state, sv_x, sv_y, x_pad, pad_between, width, height, false);
  svu.scrollview = sv;
  stack->curr_y = stack->curr_y + (height + stack->pad_between);

  return svu;
}

special_view_u vstack_add_scrollview_color(vstack_t* stack, int* id_state, int x_pad, int pad_between, int width, int height, color_t color) {
  if (item_exceeds_stack_size(stack->width, stack->height, width, height, (stack->curr_y - stack->height))) {
    printf("EXCEPTION: scroll view to big for vstack\n");
    exit(1);
  }

  enum VALIGNMENT valignment = stack->valignment;
  int sv_x, sv_y;
  scrollview_t sv;
  special_view_u svu;

  sv_x = calculateVAlignment(stack->origin_x, stack->x_pad, stack->width, width, valignment);
  sv_y = stack->origin_y + stack->curr_y;
  sv = scrollview_color(id_state, sv_x, sv_y, x_pad, pad_between, width, height, false, color);
  svu.scrollview = sv;
  stack->curr_y = stack->curr_y + (height + stack->pad_between);

  return svu;
}

hstack_t hstack(int ox, int oy, int pad_init, int y_pad, int pad_between, enum HALIGNMENT alignment) {
  return hstack_wh(ox, oy, pad_init, y_pad, pad_between, 1920, 1080, alignment);
}

hstack_t hstack_wh(int ox, int oy, int pad_init, int y_pad, int pad_between, int width, int height, enum HALIGNMENT alignment) {
  hstack_t hstack;
  hstack.origin_x = ox;
  hstack.origin_y = oy;

  hstack.pad_init = pad_init;
  hstack.pad_between = pad_between;
  hstack.y_pad = y_pad;

  hstack.curr_x = pad_init;

  hstack.width = width;
  hstack.height = height;

  hstack.halignment = alignment;
  return hstack;
}

button_t hstack_add_button(hstack_t* stack, SDL_Renderer* ren, int w, int h, int r, int g, int b, char* title, TTF_Font* font) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_x - stack->width))) {
    printf("EXCEPTION: button to big for hstack\n");
    exit(1);
  }

  enum HALIGNMENT halignment = stack->halignment;
  int btn_x, btn_y;
  button_t btn;

  btn_y = calculateHAlignment(stack->origin_y, stack->y_pad, stack->height, h, halignment);
  btn_x = stack->origin_x + stack->curr_x;
  btn = button(ren, btn_x, btn_y, w, h, r, g, b, title, font);
  stack->curr_x = stack->curr_x + (w + stack->pad_between);
  return btn;
}

hstack_t hstack_add_hstack(hstack_t* stack, int x_pad, int pad_init, int pad_between, int w, int h, enum HALIGNMENT alignment) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_x - stack->width))) {
    printf("EXCEPTION: hstack to big for hstack\n");
    exit(1);
  }

  enum HALIGNMENT halignment = stack->halignment;
  int stk_x, stk_y;
  hstack_t new_stack;

  stk_y = calculateHAlignment(stack->origin_y, stack->y_pad, stack->height, h, halignment);
  stk_x = stack->origin_x + stack->curr_x;
  new_stack = hstack_wh(stk_x, stk_y, x_pad, pad_init, pad_between, w, h, alignment);
  stack->curr_x = stack->curr_x + (w + stack->pad_between);
  return new_stack;
}

vstack_t hstack_add_vstack(hstack_t* stack, int x_pad, int pad_init, int pad_between, int w, int h, enum VALIGNMENT alignment) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_x - stack->width))) {
    printf("EXCEPTION: vstack to big for hstack\n");
    exit(1);
  }

  enum HALIGNMENT halignment = stack->halignment;
  int stk_x, stk_y;
  vstack_t new_stack;

  stk_y = calculateHAlignment(stack->origin_y, stack->y_pad, stack->height, h, halignment);
  stk_x = stack->origin_x + stack->curr_x;
  new_stack = vstack_wh(stk_x, stk_y, x_pad, pad_init, pad_between, w, h, alignment);
  stack->curr_x = stack->curr_x + (w + stack->pad_between);
  return new_stack;
}

label_t  hstack_add_label(hstack_t* stack, SDL_Renderer* ren, TTF_Font* font, char* title, int w, int h, int r, int g, int b) {
  if (item_exceeds_stack_size(stack->width, stack->height, w, h, (stack->curr_x - stack->width))) {
    printf("EXCEPTION: label to big for hstack\n");
    exit(1);
  }

  enum HALIGNMENT halignment = stack->halignment;
  int lbl_x, lbl_y;
  label_t lbl;

  lbl_y = calculateHAlignment(stack->origin_y, stack->y_pad, stack->height, h, halignment);
  lbl_x = stack->origin_x + stack->curr_x;
  lbl = label(ren, font, title, lbl_x, lbl_y, w, h, r, g, b);
  stack->curr_x = stack->curr_x + (w + stack->pad_between);
  return lbl;
}
