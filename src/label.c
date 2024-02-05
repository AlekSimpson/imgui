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
  label.rect = sdlrect(x, y, w, h);

  SDL_Color color = { label.FG_COLOR.r, label.FG_COLOR.g, label.FG_COLOR.b };

  label.surface = TTF_RenderText_Solid(font, title, color);
  label.texture = SDL_CreateTextureFromSurface(ren, label.surface);

  return label;
}

void render_label(SDL_Renderer* ren, label_t* lbl) {
  SDL_RenderCopy(ren, lbl->texture, NULL, &lbl->rect);
}
