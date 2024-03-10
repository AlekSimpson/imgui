#include <stdbool.h>

#include "../include/scrollview.h"
#include "../include/button.h"
#include "../include/color.h"

scrollview_t scrollview(int* id_state, int ox, int oy, int x_pad, int pad_between, int width, int height, bool ldo) {
  scrollview_t sv;

  sv.id = *id_state + 1;
  *id_state = *id_state + 1;

  sv.origin_x = ox;
  sv.origin_y = oy;
  sv.width = width;
  sv.height = height;

  sv.scroll_y = 0;
  sv.x_pad = x_pad;
  sv.curr_y = oy + pad_between;
  sv.max_height = sv.curr_y;
  sv.min_height = oy + height - pad_between - 50;
  sv.pad_between = pad_between;
  sv.list_does_overflow = ldo;
  sv.is_active = false;
  // sv.color = create_color(255, 255, 255);

  return sv;
}

scrollview_t scrollview_color(int* id_state, int ox, int oy, int x_pad, int pad_between, int width, int height, bool ldo, color_t color) {
  scrollview_t sv;

  sv.id = *id_state + 1;
  *id_state = *id_state + 1;

  sv.origin_x = ox;
  sv.origin_y = oy;
  sv.width = width;
  sv.height = height;

  sv.scroll_y = 0;
  sv.x_pad = x_pad;
  sv.curr_y = oy + pad_between;
  sv.max_height = sv.curr_y;
  sv.min_height = oy + height - pad_between - 50;
  sv.pad_between = pad_between;
  sv.list_does_overflow = ldo;
  sv.is_active = false;
  sv.color = color;

  return sv;
}

void scrollview_update(scrollview_t* sv) {
  sv->is_active = true;
}

button_t scrollview_add_button(scrollview_t* sv, SDL_Renderer* ren, int w, int h, int r, int g, int b, char* title, TTF_Font* font) {
  button_t btn;
  int btn_x, btn_y;

  btn_x = sv->origin_x + sv->x_pad;
  btn_y = sv->curr_y;
  sv->curr_y = sv->curr_y + sv->pad_between + h;

  btn = tag_button(ren, btn_x, btn_y, w, h, r, g, b, title, font, sv->id);

  sv->list_does_overflow = (sv->curr_y > sv->height);

  return btn;
}

button_t scrollview_add_button_color(scrollview_t* sv, SDL_Renderer* ren, int w, int h, color_t* color, char* title, TTF_Font* font) {
  button_t btn;
  int btn_x, btn_y;

  btn_x = sv->origin_x + sv->x_pad;
  btn_y = sv->curr_y;
  sv->curr_y = sv->curr_y + sv->pad_between + h;

  btn = tag_button(ren, btn_x, btn_y, w, h, color->r, color->g, color->b, title, font, sv->id);

  sv->list_does_overflow = (sv->curr_y > sv->height);

  return btn;
}
