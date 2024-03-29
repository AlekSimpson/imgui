#include <stdbool.h>
#include "color.h"
#include "button.h"
#include "label.h"
#include "scene.h"

#ifndef __MAIN_H__
#define __MAIN_H__

#define SDL_MAIN_HANDLED

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define FPS 60

typedef struct {
  bool quit;
  // scene_t main_scene;
  // scene_t sheet_scene;
  scene_t* scenes;
  int curr_scene;
  color_t BG_COLOR;
  color_t SECONDARY_COLOR;
  color_t FG_COLOR;
  TTF_Font* FONT;
} AppState;

void handle_input(SDL_Event*, AppState*);
void render(SDL_Renderer*, AppState*, bool debug);
color_t get_current_color(AppState*);
void print_carousel(color_t*);
void handle_key_input(SDL_Event*, AppState*);
void update(AppState* as);
AppState* heap_setup();
void app_loop(SDL_Renderer*, SDL_Window*);
void handle_ui_button_input(char* button_title, AppState* as);
bool is_inside_scrollview(scene_t* curr_scene);

// scene_t state_get_curr_scene(AppState*);

typedef enum {
  SCROLLVIEW_T
} UI_TYPE;

int DEBUG_X;
int DEBUG_Y;
int DEBUG_W;
int DEBUG_H;

void attach_to_ui_debug(UI_TYPE type, special_view_u* ui_element);

#endif

// Window:
//              1920
//      ------------------ x
//      |
//      |
// 1080 |
//      | 
//      |
//      y
