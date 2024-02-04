#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "../include/color.h"
#include "../include/button.h"
#include "../include/main.h"
#include "../include/label.h"
#include "../include/scene.h"
#include "../include/vstack.h"

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
  for (int i = 0; i < scene.buttonsc; i++) {
    render_button(ren, &scene.buttons[i], as_p->FONT);
  }

  // TODO: draw labels
  // for (int i = 0; i < scene.labelsc; i++) {
    // render_label(ren, &scene.labels[i]);
  // }

  SDL_RenderPresent(ren); // RENDER END
}

void update(AppState* as) {
  scene_t curr_scene = state_get_curr_scene(as);

  for (int i = 0; i < curr_scene.buttonsc; i++) {
    if (button_was_pressed(&curr_scene.buttons[i])) {
      handle_ui_button_input(curr_scene.buttons[i].title, as);
    }
  }
}

void handle_input(SDL_Event* event, AppState* as_ptr) {
  scene_t curr_scene = state_get_curr_scene(as_ptr);
  while (SDL_PollEvent(event) != 0) {
    switch (event->type) {
      case SDL_KEYDOWN:
        handle_key_input(event, as_ptr);
        break;
      case SDL_MOUSEBUTTONDOWN:
        for (int i = 0; i < curr_scene.buttonsc; i++) {
          button_process_event(&curr_scene.buttons[i], event);
        }
        break;
      default:
        break;
    }
  }
}

void handle_ui_button_input(char* button_title, AppState* as) {
  if (strcmp("Quit", button_title) == 0) {
      as->quit = true;
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
  TTF_Font* font = TTF_OpenFont("/home/alek/Desktop/projects/imgui/assets/FreeSans.ttf", 24);

  if (font == NULL) {
    printf("failed to load font\n");
    return;
  }

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

  // SDL_Renderer* ren, int x, int y, int w, int h, int r, int g, int b, char* title, TTF_Font* font
  // MARK: BUTTONS
  // main view
  button_t main_buttons[3]; // 1920w, 1080h
  vstack_t main_button_stack = vstack(0, 0, 0, 10, CENTER);
  main_buttons[0] = stack_add_button(&main_button_stack, ren, 500, 100, 0, 0, 255, "New Sheet", font);
  main_buttons[1] = stack_add_button(&main_button_stack, ren, 245, 100, 0, 0, 255, "Settings", font);
  main_buttons[2] = stack_add_button(&main_button_stack, ren, 245, 100, 0, 0, 255, "Quit", font);

  //sheet view
  button_t sv_buttons[3];
  sv_buttons[0] = button(ren, 0, 0, 0, 0, 0, 0, 0, "Save File", font);
  sv_buttons[1] = button(ren, 0, 0, 0, 0, 0, 0, 0, "Main Menu", font);
  sv_buttons[2] = button(ren, 0, 0, 0, 0, 0, 0, 0, "null", font);

  // MARK: SCENES
  AppState as;
  as.quit = false;
  as.main_scene = scene("main", &BG_COLOR, 0, 0, main_labels, main_buttons);
  as.sheet_scene = scene("sheet scene", &BG_COLOR, 0, 0, sheet_labels, sv_buttons);
  as.curr_scene = 0;
  as.BG_COLOR = BG_COLOR;
  as.SECONDARY_COLOR = SECONDARY_COLOR;
  as.FG_COLOR = FG_COLOR;
  as.FONT = font;

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


