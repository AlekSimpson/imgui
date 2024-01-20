#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../include/color.h"
#include "../include/button.h"
#include "../include/main.h"
#include "../include/label.h"
#include "../include/scene.h"

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

  app_loop(ren, win);

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
  //for (int i = 0; i < scene.buttonsc; i++) {
  //  printf("%s\n", scene.buttons[i].title);
  //}

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
  while (SDL_PollEvent(event) != 0) {
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

void app_loop(SDL_Renderer* ren, SDL_Window* win) {
  // SETUP
  int FRAME_DELAY = 1000 / FPS;
  uint32_t frameStart;
  int frameTime;

  color_t BG_COLOR = create_color(11, 19, 43);
  color_t SECONDARY_COLOR = create_color(28, 37, 65);
  color_t FG_COLOR = create_color(58, 80, 107);

  // MARK: LABELS
  // main view
  label_t main_labels[2];
  main_labels[0] = label("DND", 400, 400, 100, 100, 58, 80, 107); // title_label;
  main_labels[1] = label("Choose Sheet:", 400, 500, 300, 100, 58, 80, 107); // sheet_label;

  // sheet view
  SDL_Rect r = sdlrect(0,0,0,0);
  label_t sheet_labels[4];
  sheet_labels[0] = label("Character Name", 0, 0, 0, 0, 11, 19, 43);
  sheet_labels[1] = label("Race", 0, 0, 0, 0, 11, 19, 43);
  sheet_labels[2] = label("Class", 0, 0, 0, 0, 11, 19, 43);
  sheet_labels[3] = label("Class", 0, 0, 0, 0, 11, 19, 43);

  // MARK: BUTTONS
  // main view
  button_t main_buttons[3];
  main_buttons[0] = button(400, 700, 500, 100, 0, 0, 255, "New Sheet");
  main_buttons[1] = button(400, 800, 250, 100, 0, 0, 255, "Quit");
  main_buttons[2] = button(650, 800, 250, 100, 0, 0, 255, "Settings");

  //sheet view
  button_t sv_buttons[3];
  sv_buttons[0] = button(0, 0, 0, 0, 0, 0, 0, "Save File");
  sv_buttons[1] = button(0, 0, 0, 0, 0, 0, 0, "Main Menu");
  sv_buttons[2] = button(0, 0, 0, 0, 0, 0, 0, "null");

  // MARK: SCENES
  AppState as;
  as.quit = false;
  as.main_scene = scene("main", &BG_COLOR, 0, 0, main_labels, main_buttons);
  as.sheet_scene = scene("sheet scene", &BG_COLOR, 0, 0, sheet_labels, sv_buttons);
  as.curr_scene = 0;
  as.BG_COLOR = BG_COLOR;
  as.SECONDARY_COLOR = SECONDARY_COLOR;
  as.FG_COLOR = FG_COLOR;

  // App Loop Begins
  SDL_Event e;

  // While application is running
  while (!as.quit) {
    frameStart = SDL_GetTicks();

    handle_input(&e, &as);
    update(&as);
    render(ren, &as);

    frameTime = SDL_GetTicks() - frameStart;

    if (FRAME_DELAY > frameTime) {
      SDL_Delay(FRAME_DELAY - frameTime);
    }
  }

  // Clearn up SDL stuff
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

// App Color Theme
// 11, 19,  43 BG
// 28, 37,  65 SEC
// 58, 80, 107 FG

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


