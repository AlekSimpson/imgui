#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#include "../include/label.h"
#include "../include/color.h"
#include "../include/button.h"

label_t label(SDL_Renderer* ren, TTF_Font* font, char* title, int x, int y, int w, int h, int r, int g, int b) {
  label_t label;

  label.text = title;
  label.FG_COLOR = create_color(r, g, b);

  SDL_Color color = { label.FG_COLOR.r, label.FG_COLOR.g, label.FG_COLOR.b };

  label.surface = TTF_RenderText_Solid(font, title, color);
  label.texture = SDL_CreateTextureFromSurface(ren, label.surface);

  SDL_Rect text_rect = {
    .x = (x + (w / 2)) - (label.surface->w / 2),
    .y = (y + (h / 2)) - (label.surface->h / 2),
    .w = label.surface->w,
    .h = label.surface->h
  };

  label.rect = text_rect;

  return label;
}

label_t label_white(SDL_Renderer* ren, TTF_Font* font, char* title, int x, int y, int w, int h) {
  label_t label;

  label.text = title;
  label.FG_COLOR = create_color(255, 255, 255);

  SDL_Color color = { 255, 255, 255 };

  label.surface = TTF_RenderText_Solid(font, title, color);
  label.texture = SDL_CreateTextureFromSurface(ren, label.surface);

  SDL_Rect text_rect = {
    .x = (x + (w / 2)) - (label.surface->w / 2),
    .y = (y + (h / 2)) - (label.surface->h / 2),
    .w = label.surface->w,
    .h = label.surface->h
  };

  label.rect = text_rect;

  return label;
}

label_t label_black(SDL_Renderer* ren, TTF_Font* font, char* title, int x, int y, int w, int h) {
  label_t label;

  label.text = title;
  label.FG_COLOR = create_color(0, 0, 0);

  SDL_Color color = { 0, 0, 0 };

  label.surface = TTF_RenderText_Solid(font, title, color);
  label.texture = SDL_CreateTextureFromSurface(ren, label.surface);

  SDL_Rect text_rect = {
    .x = (x + (w / 2)) - (label.surface->w / 2),
    .y = (y + (h / 2)) - (label.surface->h / 2),
    .w = label.surface->w,
    .h = label.surface->h
  };

  label.rect = text_rect;

  return label;
}

void render_label(SDL_Renderer* ren, label_t* lbl) {
  SDL_RenderCopy(ren, lbl->texture, NULL, &lbl->rect);
}
