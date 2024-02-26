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
#include "../include/scrollview.h"

void attach_to_ui_debug(UI_TYPE type, special_view_u* ui_element) {
  switch (type) {
    case SCROLLVIEW_T:
      DEBUG_X = ui_element->scrollview.origin_x;
      DEBUG_Y = ui_element->scrollview.origin_y;
      DEBUG_W = ui_element->scrollview.width;
      DEBUG_H = ui_element->scrollview.height;
      break;
    default:
      DEBUG_X = 0;
      DEBUG_Y = 0;
      DEBUG_W = 100;
      DEBUG_H = 100;
      break;
  }
}

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
  // scene_t scene = state_get_curr_scene(as_p);
  scene_t scene = as_p->scenes[as_p->curr_scene];

  //
  // RENDER START
  //
  SDL_RenderClear(ren); 


  // draw background
  SDL_SetRenderDrawColor(ren, as_p->BG_COLOR.r, as_p->BG_COLOR.g, as_p->BG_COLOR.b, 255);
  SDL_RenderClear(ren);

  color_t color;
  if (debug) {
    //
    // DEBUG
    //
    color = create_color(0, 255, 0);
    draw_rectangle(ren, &color, true, DEBUG_X, DEBUG_Y, DEBUG_W, DEBUG_H);
  }

  for (int i = 0; i < scene.special_viewsc; i++) {
    color = create_color(scene.special_views[i].scrollview.color.r, scene.special_views[i].scrollview.color.g, scene.special_views[i].scrollview.color.b);
    draw_rectangle(ren, &color, true, scene.special_views[i].scrollview.origin_x, scene.special_views[i].scrollview.origin_y, scene.special_views[i].scrollview.width, scene.special_views[i].scrollview.height);
  }


  // draw buttons
  int curr_scrollview_tag;
  button_t curr_btn;
  scrollview_t curr_scrollview;
  for (int i = 0; i < scene.buttonsc; i++) {
    curr_btn = scene.buttons[i];
    curr_scrollview_tag = curr_btn.scrollview_tag;

    // before rending the button we need to check if it should be display IF its tied to a scrollview

    if (curr_scrollview_tag != -1) {
      // curr_scrollview = as_p->main_scene.special_views[curr_scrollview_tag - 1].scrollview;
      curr_scrollview = as_p->scenes[as_p->curr_scene].special_views[curr_scrollview_tag - 1].scrollview;

      curr_btn.rect.y -= curr_scrollview.scroll_y;

      // check if (btn_x, btn_y) and (btn_x, btn_y + btn_h) is in range of scrollview height
      int btn_y_top = curr_btn.rect.y;

      // check if the button is not in bounds
      if (btn_y_top < curr_scrollview.origin_y || btn_y_top >= ((curr_scrollview.origin_y + curr_scrollview.height) - curr_btn.rect.h)) {
        continue; // if so then don't display it
      }
    }


    render_button(ren, &curr_btn, as_p->FONT);
  }

  // draw labels
  for (int i = 0; i < scene.labelsc; i++) {
    render_label(ren, &scene.labels[i]);
  }


  SDL_RenderPresent(ren); 
  //
  // RENDER END
  //
}

void update(AppState* as) {
  scene_t curr_scene = as->scenes[as->curr_scene];

  for (int i = 0; i < curr_scene.buttonsc; i++) {
    if (button_was_pressed(&curr_scene.buttons[i])) {
      handle_ui_button_input(curr_scene.buttons[i].title, as);
    }
  }
}

// TODO: Make system work with multiple scroll views, this implementation will only with one scroll view per scene which is fine for now
bool is_inside_scrollview(scene_t* curr_scene) {
  int mx, my;
  SDL_GetMouseState(&mx, &my);

  int w, h;
  bool x_is_inbounds, y_is_inbounds;
  scrollview_t curr_sv;
  for (int i = 0; i < curr_scene->special_viewsc; i++) {
    curr_sv = curr_scene->special_views[i].scrollview;
    w = curr_sv.width;
    h = curr_sv.height;

    x_is_inbounds = (mx >= curr_sv.origin_x && mx < curr_sv.origin_x + w);
    y_is_inbounds = (my >= curr_sv.origin_y && my < curr_sv.origin_y + h);

    if (x_is_inbounds && y_is_inbounds) {
      return true;
    }
  }

  return false;
}

void handle_input(SDL_Event* event, AppState* as_ptr) {
  // scene_t curr_scene = state_get_curr_scene(as_ptr);
  scene_t curr_scene = as_ptr->scenes[as_ptr->curr_scene];
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
      case SDL_MOUSEWHEEL:
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        bool mouse_in_view = is_inside_scrollview(&curr_scene);

        if (mouse_in_view && curr_scene.special_viewsc > 0) {
          curr_scene.special_views[0].scrollview.scroll_y += event->wheel.y * 20; // can adjust sensitivity with the muliplier
          curr_scene.special_views[0].scrollview.is_active = true;
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
      break;
    default:
      break;
  }
}

void app_loop(SDL_Renderer* ren, SDL_Window* win) {
  // SETUP
  char* FONT_PATH = "/home/alek/Desktop/projects/imgui/assets/FreeSans.ttf";
  int FRAME_DELAY = 1000 / FPS;
  uint32_t frameStart;
  int frameTime;
  TTF_Font* font24 = TTF_OpenFont(FONT_PATH, 24);
  TTF_Font* font_title = TTF_OpenFont(FONT_PATH, 60);

  // setup to track most current ID so that when a new one is made we know what the next ID should be
  int id_state = 0;
  int* ID_STATE;
  ID_STATE = &id_state;

  if (font24 == NULL || font_title == NULL) {
    printf("failed to load font\n");
    return;
  }

  color_t BG_COLOR = create_color(52, 73, 85);
  color_t SECONDARY_COLOR = create_color(74, 101, 114);
  color_t FG_COLOR = create_color(35, 47, 52);

  // MARK: LABELS
  /// view declarations
  //
  int main_label_count = 1;
  int main_button_count = 8;
  int main_special_count = 1;

  int sheet_button_count = 3;
  int sheet_label_count = 4;
  int sheet_special_count = 0;

  button_t main_buttons[main_button_count];
  label_t  main_labels[main_label_count];
  special_view_u main_special_views[main_special_count];

  label_t  sheet_labels[sheet_label_count];
  button_t sheet_buttons[sheet_button_count];
  special_view_u sheet_special_views[sheet_special_count];

  /// view definitions
  //
  vstack_t main_root_stack = vstack(0, 0, 50, 20, 20, CENTER); // the scenes root stack always starts at coordinates (0, 0)
  main_labels[0]  = vstack_add_label(&main_root_stack, ren, font_title, "Character Sheet Manager", 250, 100, 255, 255, 255);

  special_view_u main_sv_view = vstack_add_scrollview_color(&main_root_stack, ID_STATE, 10, 10, 500, 600, create_color(113, 150, 168)); // scrollview_t

  // attach to debug
  attach_to_ui_debug(SCROLLVIEW_T, &main_sv_view);

  main_special_views[0] = main_sv_view; 
  main_buttons[0] = vstack_add_button(&main_root_stack, ren, 500, 100, 74, 101, 114, "New Sheet", font24);

  main_buttons[1] = scrollview_add_button_color(&main_sv_view.scrollview, ren, 400, 125, &SECONDARY_COLOR, "item A", font24);
  main_buttons[2] = scrollview_add_button_color(&main_sv_view.scrollview, ren, 400, 125, &SECONDARY_COLOR, "item B", font24);
  main_buttons[3] = scrollview_add_button_color(&main_sv_view.scrollview, ren, 400, 125, &SECONDARY_COLOR, "item C", font24);
  main_buttons[4] = scrollview_add_button_color(&main_sv_view.scrollview, ren, 400, 125, &SECONDARY_COLOR, "item D", font24);
  main_buttons[5] = scrollview_add_button_color(&main_sv_view.scrollview, ren, 400, 125, &SECONDARY_COLOR, "item E", font24);

  hstack_t button_hstack = vstack_add_hstack(&main_root_stack, 0, 0, 60, 500, 100, MIDDLE);

  main_buttons[6] = hstack_add_button(&button_hstack, ren, 220, 100, 74, 101, 114, "Settings", font24);
  main_buttons[7] = hstack_add_button(&button_hstack, ren, 220, 100, 74, 101, 114, "Quit", font24);

  // MARK: SCENES
  scene_t scenes[2];
  scenes[0] = scene("MAIN-SCENE", &BG_COLOR, main_button_count, main_label_count, main_special_count, main_labels, main_buttons, main_special_views);
  scenes[1] = scene("SHEET-SCENE", &BG_COLOR, sheet_button_count, sheet_label_count, sheet_special_count, sheet_labels, sheet_buttons, sheet_special_views);

  AppState as;
  as.quit = false;
  as.scenes = scenes;
  as.curr_scene = 0;
  as.BG_COLOR = BG_COLOR;
  as.SECONDARY_COLOR = SECONDARY_COLOR;
  as.FG_COLOR = FG_COLOR;
  as.FONT = font24;

  // App Loop Begins
  SDL_Event e;
  bool DEBUG = false;

  // While application is running
  while (!as.quit) {
    frameStart = SDL_GetTicks();

    handle_input(&e, &as);
    update(&as);
    render(ren, &as, DEBUG);

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
//
// Window:
//            900
//     ------------------ x
//     |
//     |
// 850 |
//     | 
//     |
//     y


