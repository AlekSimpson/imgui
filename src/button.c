#include "../include/button.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

button_t button(int x, int y, int w, int h, int r, int g, int b) {
  button_t button;
  button.rect = sdlrect(x, y, w, h);
  button.color = create_color(r, g, b);
  button.pressed = false;
  return button;
}

void button_process_event(button_t* btn, SDL_Event* ev) {
  if (
    ev->button.button == SDL_BUTTON_LEFT &&
    ev->button.x >= btn->rect.x &&
    ev->button.x <= (btn->rect.x + btn->rect.w) &&
    ev->button.y >= btn->rect.y &&
    ev->button.y <= (btn->rect.y + btn->rect.h)
  ) {
    btn->pressed = true;
  }
}

void render_button(SDL_Renderer* ren, button_t* btn) {
  // draw button
  draw_rectangle(ren, &btn->color, true, btn->rect.x, btn->rect.y, btn->rect.w, btn->rect.h);
}

bool button_was_pressed(button_t* btn) {
  // if button press detected - reset it so it wouldn't trigger twice
  if (btn->pressed) {
    btn->pressed = false;
    return true;
  }
  return false;
}

SDL_Rect sdlrect(int x, int y, int w, int h) {
  SDL_Rect rect = {.x = x, .y = y, .w = w, .h = h};
  return rect;
}

void draw_rectangle(SDL_Renderer* ren, color_t* color, bool fill, int x, int y, int w, int h) {
  SDL_Rect rect = { .x = x, .y = y, .w = w, .h = h };
  SDL_SetRenderDrawColor(ren, color->r, color->g, color->b, 255);
  SDL_RenderDrawRect(ren, &rect);
  if (fill) {
    SDL_RenderFillRect(ren, &rect);
  }
}
