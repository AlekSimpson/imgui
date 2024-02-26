#include "../include/scene.h"
#include "../include/scrollview.h"

//            char* name, color_t* color, int bc, int lc, label_t* labels, label_t* buttons
scene_t scene(char* name, color_t* color, int bc, int lc, int special_viewsc, label_t* labels, button_t* buttons, special_view_u* special_views) {
  scene_t scene;
  scene.scene_name = name;
  scene.bg_color = *color;
  scene.buttonsc = bc;
  scene.labelsc = lc;
  scene.special_viewsc = special_viewsc;
  scene.labels = labels;
  scene.buttons = buttons;
  scene.special_views = special_views;

  return scene;
}
