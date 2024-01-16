#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../include/color.h"
#include "../include/button.h"
#include "../include/main.h"
#include "../include/label.h"

int main(int argc, char* argv[]) {
  SDL_Window* win   = NULL;
  SDL_Renderer* ren = NULL;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &win, &ren);

  if (TTF_Init() == -1) {
    printf("error initializing SDL TFF\n");
    return 1;
  }

  if (win == NULL || ren == NULL) {
    printf("error initializing renderer\n");
    return 1;
  }

  AppState* as = setup();
  SDL_Event e;

  // printf("%s\n", );

  // While application is running
  while (!as->quit) {
    handle_input(&e, as);
    update(as);
    render(ren, as);
  }

  // Clearn up SDL stuff
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  // free application memory
  free(as);

  return 0;
}

void render(SDL_Renderer* ren, AppState* as_p) {
  // get current scene to render
  scene_t scene = state_get_curr_scene(as_p);

  SDL_RenderClear(ren); // RENDER START

  // draw background
  SDL_SetRenderDrawColor(ren, as_p->BG_COLOR.r, as_p->BG_COLOR.g, as_p->BG_COLOR.b, 255);
  SDL_RenderClear(ren);

  // draw buttons
  for (int i = 0; i < scene.buttonsc; i++) {
    printf("%s\n", scene.buttons[i].title);
  }

  // TODO: draw labels
  // for (int i = 0; i < scene.labelsc; i++) {
    // render_label(ren, &scene.labels[i]);
  // }

  SDL_RenderPresent(ren); // RENDER END
}

void update(AppState* as) {
  // if (button_was_pressed(&as->scenes[0].buttons[0])) {
    // printf("button was pressed\n");
  // }
}

void handle_input(SDL_Event* event, AppState* as_ptr) {
  while (SDL_PollEvent(event)) {
    switch (event->type) {
      case SDL_KEYDOWN:
        handle_key_input(event, as_ptr);
        break;
      case SDL_MOUSEBUTTONDOWN:
        break;
      default:
        break;
    }
  }
}

void handle_key_input(SDL_Event* event, AppState* as_p) {
  switch (event->key.keysym.sym) {
    case SDL_QUIT:
      as_p->quit = true;
      break;
    case SDLK_q:
      as_p->quit = true;
      break;
    case SDLK_w:
      // as_p->scenes[0].bg_color = c;
      break;
    default:
      break;
  }
}

// App Color Theme
// 11, 19,  43
// 28, 37,  65
// 58, 80, 107

// button declaration example:
// button_t button = { .rect = sdlrect(425, 450, 85, 50), .color = create_color(73, 82, 97), .pressed = false }; 

AppState* setup() {
  color_t BG_COLOR = create_color(11, 19, 43);
  color_t SECONDARY_COLOR = create_color(28, 37, 65);
  color_t FG_COLOR = create_color(58, 80, 107);

  // MARK: LABELS
  // main view
  label_t main_labels[2];
  SDL_Rect rect1 = sdlrect(400, 400, 100, 100); // title label
  SDL_Rect rect2 = sdlrect(400, 500, 300, 100); // choose sheet label
  label_t title_label = { .text = "DND", .fg_color = FG_COLOR, .rect = &rect1 }; // title label
  label_t sheet_label = { .text = "Choose Sheet:", .fg_color = FG_COLOR, .rect = &rect2 }; // choose sheet label
  main_labels[0] = title_label;
  main_labels[1] = sheet_label;

  // sheet view
  SDL_Rect r = sdlrect(0,0,0,0);
  label_t sheet_labels[4];
  label_t name_label  = { .text = "Character Name", .fg_color = BG_COLOR, .rect = &r };
  label_t race_label  = { .text = "Race", .fg_color = BG_COLOR, .rect = &r }; 
  label_t class_label = { .text = "Class", .fg_color = BG_COLOR, .rect = &r };
  label_t level_label = { .text = "Class", .fg_color = BG_COLOR, .rect = &r };
  sheet_labels[0] = name_label;
  sheet_labels[1] = race_label;
  sheet_labels[2] = class_label;
  sheet_labels[3] = level_label;

  // MARK: BUTTONS
  // main view
  button_t main_buttons[3];
  button_t new_button      = { .rect = sdlrect(400, 700, 500, 100), .color = create_color(0, 0, 255), .title = "New Sheet", .pressed = false };
  button_t quit_button     = { .rect = sdlrect(400, 800, 250, 100), .color = create_color(0, 0, 255), .title = "Quit", .pressed = false };
  button_t settings_button = { .rect = sdlrect(650, 800, 250, 100), .color = create_color(0, 0, 255), .title = "Settings", .pressed = false };
  main_buttons[0] = new_button;
  main_buttons[1] = quit_button;
  main_buttons[2] = settings_button;

  //sheet view
  button_t sv_buttons[2];
  button_t save_button = { .rect = sdlrect(0,0,0,0), .color = create_color(0,0,0), .title = "Save File", .pressed = false };
  button_t mm_button   = { .rect = sdlrect(0,0,0,0), .color = create_color(0,0,0), .title = "Main Menu", .pressed = false };
  sv_buttons[0] = save_button;
  sv_buttons[1] = mm_button;

  // MARK: SCENES
  scene_t main_scene = { .scene_name = "main", .bg_color = BG_COLOR, .buttonsc = 3, .labelsc = 2, .labels = main_labels, .buttons = main_buttons };
  scene_t sheet_scene = { .scene_name = "sheet scene", .bg_color = BG_COLOR, .buttonsc = 2, .labelsc = 4, .labels = sheet_labels, .buttons = sv_buttons };

  AppState* as = malloc(sizeof(AppState));
  as->quit = false;
  as->main_scene = main_scene;
  as->sheet_scene = sheet_scene;
  as->curr_scene = 0;
  as->BG_COLOR = BG_COLOR;
  as->SECONDARY_COLOR = SECONDARY_COLOR;
  as->FG_COLOR = FG_COLOR;

  return as;
}

scene_t state_get_curr_scene(AppState* as) {
  switch (as->curr_scene) {
    case 0:
      return as->main_scene;
    case 1:
      return as->sheet_scene;
    default:
      break;
  }
}

// Window:
//            900
//     ------------------ x
//     |
//     |
// 850 |
//     | 
//     |
//     y


