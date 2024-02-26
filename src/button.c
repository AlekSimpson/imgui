#include "../include/button.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

button_t button(SDL_Renderer* ren, int x, int y, int w, int h, int r, int g, int b, char* title, TTF_Font* font) {
  button_t button;
  SDL_Color white = {255, 255, 255};

  button.rect = sdlrect(x, y, w, h);
  button.color = create_color(r, g, b);
  button.title = title;
  button.pressed = false;
  button.surface = TTF_RenderText_Solid(font, title, white);
  button.texture = SDL_CreateTextureFromSurface(ren, button.surface);
  button.scrollview_tag = -1; // -1 will be the "null" code for this value

  return button;
}

button_t tag_button(SDL_Renderer* ren, int x, int y, int w, int h, int r, int g, int b, char* title, TTF_Font* font, int tag) {
  button_t button;
  SDL_Color white = {255, 255, 255};

  button.rect = sdlrect(x, y, w, h);
  button.color = create_color(r, g, b);
  button.title = title;
  button.pressed = false;
  button.surface = TTF_RenderText_Solid(font, title, white);
  button.texture = SDL_CreateTextureFromSurface(ren, button.surface);
  button.scrollview_tag = tag;

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

void render_button(SDL_Renderer* ren, button_t* btn, TTF_Font* font) {
  // draw button
  draw_rectangle(ren, &btn->color, true, btn->rect.x, btn->rect.y, btn->rect.w, btn->rect.h);

  SDL_Rect text_rect = {
    .x = (btn->rect.x + (btn->rect.w / 2)) - (btn->surface->w / 2),
    .y = (btn->rect.y + (btn->rect.h / 2)) - (btn->surface->h / 2),
    .w = btn->surface->w,
    .h = btn->surface->h
  };

  SDL_RenderCopy(ren, btn->texture, NULL, &text_rect);
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
