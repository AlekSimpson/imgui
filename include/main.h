#include "color.h"
#include "button.h"
#include "label.h"

#ifndef __MAIN_H__
#define __MAIN_H__

#define SDL_MAIN_HANDLED

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 850

typedef struct {
  char* scene_name;
  color_t bg_color;
  int buttonsc;
  int labelsc;
  label_t* labels;
  button_t buttons[3];
} scene_t;

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
AppState* setup();

scene_t state_get_curr_scene(AppState*);

// scene_t create_scene(char*, color_t, int, int);

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
