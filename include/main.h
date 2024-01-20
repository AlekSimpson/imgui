#include "color.h"
#include "button.h"
#include "label.h"
#include "scene.h"

#ifndef __MAIN_H__
#define __MAIN_H__

#define SDL_MAIN_HANDLED

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 850
#define FPS 30

typedef struct {
  bool quit;
  scene_t main_scene;
  scene_t sheet_scene;
  int curr_scene;
  color_t BG_COLOR;
  color_t SECONDARY_COLOR;
  color_t FG_COLOR;
} AppState;

void handle_input(SDL_Event*, AppState*);
void render(SDL_Renderer*, AppState*);
color_t get_current_color(AppState*);
void print_carousel(color_t*);
void handle_key_input(SDL_Event*, AppState*);
void update(AppState* as);
AppState* heap_setup();
void app_loop(SDL_Renderer*, SDL_Window*);

scene_t state_get_curr_scene(AppState*);

#endif

// Window:
//            900
//     ------------------ x
//     |
//     |
// 850 |
//     | 
//     |
//     y
