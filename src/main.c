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
#include "../include/stack.h"

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

void render(SDL_Renderer* ren, AppState* as_p, bool debug) {
  // get current scene to render
  scene_t scene = state_get_curr_scene(as_p);

  SDL_RenderClear(ren); // RENDER START


  // draw background
  SDL_SetRenderDrawColor(ren, as_p->BG_COLOR.r, as_p->BG_COLOR.g, as_p->BG_COLOR.b, 255);
  SDL_RenderClear(ren);

  if (debug) {
    //
    // DEBUG
    //
    color_t color = create_color(255, 0, 0);
    draw_rectangle(ren, &color, true, 0, 160, 1920, 100);
  }

  // draw buttons
  for (int i = 0; i < scene.buttonsc; i++) {
    render_button(ren, &scene.buttons[i], as_p->FONT);
  }

  // draw labels
  for (int i = 0; i < scene.labelsc; i++) {
    render_label(ren, &scene.labels[i]);
  }

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
  int main_label_count = 2;
  int main_button_count = 3;

  int sheet_button_count = 3;
  int sheet_label_count = 4;

  button_t main_buttons[main_button_count]; // 1920w, 1080h
  label_t main_labels[main_label_count];
  label_t sheet_labels[sheet_label_count];
  button_t sheet_buttons[sheet_button_count];

  vstack_t main_root_stack = vstack(0, 0, 50, 20, CENTER); // the scenes root stack always starts at coordinates (0, 0)
  main_buttons[0] = vstack_add_button(&main_root_stack, ren, 500, 100, 0, 0, 255, "New Sheet", font);

  hstack_t button_hstack = vstack_add_hstack(&main_root_stack, ((1920 / 2)), 10, 1920, 100, MIDDLE);

  main_buttons[1] = hstack_add_button(&button_hstack, ren, 220, 100, 0, 0, 255, "Settings", font);
  main_buttons[2] = hstack_add_button(&button_hstack, ren, 220, 100, 0, 0, 255, "Quit", font);

  // MARK: SCENES
  AppState as;
  as.quit = false;
  as.main_scene = scene("MAIN-SCENE", &BG_COLOR, main_button_count, main_label_count, main_labels, main_buttons);
  as.sheet_scene = scene("SHEET-SCENE", &BG_COLOR, sheet_button_count, sheet_label_count, sheet_labels, sheet_buttons);
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
    render(ren, &as, true);

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

// to add an hstack to the mainstack
// hstack_t test_hstack = vstack_add_hstack(&main_button_stack, 25, 0, 600, 300, TOP);

// main_buttons[3] = hstack_add_button(&test_hstack, ren, 245, 100, 0, 255, 0, "A", font);
// main_buttons[4] = hstack_add_button(&test_hstack, ren, 245, 100, 0, 255, 0, "B", font);

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


