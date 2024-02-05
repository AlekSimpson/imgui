#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"
#include "../include/button.h"

vstack_t vstack(int ox, int oy, int x_pad, int y_pad, enum VALIGNMENT alignment) {
  return vstack_wh(ox, oy, x_pad, y_pad, 1920, 1080, alignment);
}

vstack_t vstack_wh(int ox, int oy, int x_pad, int y_pad, int pad_between, int width, int height, enum VALIGNMENT alignment) {
  vstack_t vstack;
  vstack.origin_x = ox;
  vstack.origin_y = oy;
  vstack.x_pad = x_pad;
  vstack.y_pad = y_pad;
  vstack.pad_between = pad_between;

  vstack.curr_x = x_pad;
  vstack.curr_y = y_pad;

  vstack.width = width;
  vstack.height = height;

  vstack.alignment = alignment;
  return vstack;
}

button_t vstack_add_button(vstack_t* stack, SDL_Renderer* ren, int w, int h, int r, int g, int b, char* title, TTF_Font* font) {
  enum VALIGNMENT alignment = stack->alignment;
  int x, y;
  button_t btn;

  if (w > stack->width || h > stack->height) {
    printf("button to big for vstack\n");
    exit(1);
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

vstack_t vstack_add_vstack(vstack_t* vstack, int x_pad, int y_pad, int pad_between, int w, int h, enum VALIGNMENT alignment) {
  int x, y;
  vstack_t newStack;

  switch (alignment) {
    case LEADING:
      x = (vstack->origin_x + vstack->curr_x);
      break;
    case CENTER:
      x = ((vstack->width / 2) - (w / 2)); // might need to add vstack->origin_x to this 
      break;
    case TRAILING:
      x = (vstack->origin_x + vstack->width) - (w + vstack->curr_x);
      break;
  }

  y = vstack->origin_y + vstack->curr_y;
  newStack = vstack_wh(x, y, x_pad, y_pad, pad_between, w, h, alignment);
  vstack->curr_y = vstack->curr_y + ((vstack->y_pad * 2) + h);

  return newStack;
}

hstack_t vstack_add_hstack(vstack_t* vstack, int x_pad, int y_pad, int pad_between, int w, int h, enum HALIGNMENT alignment) {
  int x, y;
  enum VALIGNMENT vstack_alignment = vstack->alignment;

  //switch (vstack_alignment) {
  //  case LEADING:
  //    x = (vstack->origin_x + vstack->curr_x);
  //    break;
  //  case CENTER:
  //    x = ((vstack->width / 2) - (w / 2)); // might need to add vstack->origin_x to this 
  //    break;
  //  case TRAILING:
  //    x = (vstack->origin_x + vstack->width) - (w + vstack->curr_x);
  //    break;
  //}
  x = 0;

  y = vstack->origin_y + vstack->curr_y;
  hstack_t newStack = hstack_wh(x, y, x_pad, y_pad, pad_between, w, h, alignment);
  vstack->curr_y = vstack->curr_y + ((vstack->y_pad * 2) + h);

  printf("HS: ox: %d, oy: %d\n", newStack.origin_x, newStack.origin_y);

  return newStack;
}

label_t vstack_add_label(vstack_t* stack, SDL_Renderer* ren, TTF_Font* font, char* title, int w, int h, int r, int g, int b) {
  enum VALIGNMENT alignment = stack->alignment;
  int x, y;
  label_t lbl;

  if (w > stack->width || h > stack->height) {
    printf("button to big for vstack\n");
    exit(1);
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
  lbl = label(ren, font, title, x, y, w, h, r, g, b);
  stack->curr_y = stack->curr_y + ((stack->y_pad * 2) + h);

  return lbl;
}

hstack_t hstack(int ox, int oy, int x_pad, int y_pad, int pad_between, enum HALIGNMENT alignment) {
  return hstack_wh(ox, oy, x_pad, y_pad, pad_between, 1920, 1080, alignment);
}

hstack_t hstack_wh(int ox, int oy, int x_pad, int y_pad, int pad_between, int width, int height, enum HALIGNMENT alignment) {
  hstack_t hstack;
  hstack.origin_x = ox;
  hstack.origin_y = oy;
  hstack.x_pad = x_pad;
  hstack.y_pad = y_pad;
  hstack.pad_between = pad_between;

  hstack.curr_x = x_pad;
  hstack.curr_y = y_pad;

  hstack.width = width;
  hstack.height = height;

  hstack.alignment = alignment;
  return hstack;
}

button_t hstack_add_button(hstack_t* stack, SDL_Renderer* ren, int w, int h, int r, int g, int b, char* title, TTF_Font* font) {
  enum HALIGNMENT alignment = stack->alignment;
  int x, y;
  button_t btn;

  if (w > stack->width || h > stack->height) {
    // button should fit inside the hstack
    printf("button to big for hstack\n");
    exit(1);
  }

  switch (alignment) {
    case TOP:
      y = (stack->origin_y + stack->curr_y);
      break;
    case CENTER:
      y = stack->origin_y + ((stack->height / 2) - (h / 2));
      break;
    case BOTTOM:
      y = (stack->origin_y + stack->height) - (h + stack->curr_y);
      break;
  }

  x = stack->origin_x + stack->curr_x;
  btn = button(ren, x, y, w, h, r, g, b, title, font);
  stack->curr_x = stack->curr_x + ((stack->x_pad * 2) + w);

  return btn;
}

hstack_t hstack_add_hstack(hstack_t* stack, int x_pad, int y_pad, int pad_between, int w, int h, enum HALIGNMENT alignment) {
  enum HALIGNMENT stack_alignment = stack->alignment;
  int x, y;

  if (w > stack->width || h > stack->height) {
    printf("hstack to big for hstack\n");
    exit(1);
  }

  switch (stack_alignment) {
    case TOP:
      y = (stack->origin_y + stack->curr_y);
      break;
    case CENTER:
      y = stack->origin_y + ((stack->height / 2) - (h / 2));
      break;
    case BOTTOM:
      y = (stack->origin_y + stack->height) - (h + stack->curr_y);
      break;
  } 

  x = stack->origin_x + stack->curr_x;
  hstack_t newStack = hstack_wh(x, y, x_pad, y_pad, pad_between, w, h, alignment);
  stack->curr_x = stack->curr_x + ((stack->x_pad * 2) + w);

  return newStack;
}

vstack_t hstack_add_vstack(hstack_t* stack, int x_pad, int y_pad, int pad_between, int w, int h, enum VALIGNMENT alignment) {
  enum HALIGNMENT stack_alignment = stack->alignment;
  int x, y;

  if (w > stack->width || h > stack->height) {
    printf("vstack to big for hstack\n");
    exit(1);
  }

  switch (stack_alignment) {
    case TOP:
      y = (stack->origin_y + stack->curr_y);
      break;
    case CENTER:
      y = stack->origin_y + ((stack->height / 2) - (h / 2));
      break;
    case BOTTOM:
      y = (stack->origin_y + stack->height) - (h + stack->curr_y);
      break;
  } 

  x = stack->origin_x + stack->curr_x;
  vstack_t newStack = vstack_wh(x, y, x_pad, y_pad, pad_between, w, h, alignment);
  stack->curr_x = stack->curr_x + ((stack->x_pad * 2) + w);

  return newStack;
}

label_t  hstack_add_label(hstack_t* stack, SDL_Renderer* ren, TTF_Font* font, char* title, int w, int h, int r, int g, int b) {
  enum VALIGNMENT alignment = stack->alignment;
  int x, y;
  label_t lbl;

  if (w > stack->width || h > stack->height) {
    printf("label to big for hstack\n");
    exit(1);
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
  lbl = label(ren, font, title, x, y, w, h, r, g, b);
  stack->curr_y = stack->curr_y + ((stack->y_pad * 2) + h);

  return lbl;
}
