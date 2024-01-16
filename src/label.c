#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#include "../include/label.h"
#include "../include/color.h"

label_t label(char* title, color_t* color, SDL_Rect* rect) {
  label_t label = { .text = title, .fg_color = *color, .rect = rect };
  return label;
}

void render_label(SDL_Renderer* ren, label_t* lbl) {
  TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
  SDL_Color sdl_color = { lbl->fg_color.r, lbl->fg_color.g, lbl->fg_color.b };
  SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, lbl->text, sdl_color); 
  SDL_Texture* message = SDL_CreateTextureFromSurface(ren, surface_message);
  SDL_RenderCopy(ren, message, NULL, &lbl->rect);
}
