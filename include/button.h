#include <SDL2/SDL.h>
#include <stdbool.h>

#include "color.h"

#ifndef __BUTTON_H__
#define __BUTTON_H__

typedef struct {
  SDL_Rect rect; // dimensions of button and position
  color_t color;
  char* title;
  bool pressed;
} button_t;

button_t button(int, int, int, int, int, int, int, char*);
void render_button(SDL_Renderer*, button_t*);
bool button_was_pressed(button_t*);
void button_process_event(button_t*, SDL_Event*);

SDL_Rect sdlrect(int, int, int, int);
void draw_rectangle(SDL_Renderer*, color_t*, bool, int, int, int, int);

#endif
