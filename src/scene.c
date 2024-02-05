#include <stdio.h>
#include <stdlib.h>

#include "../include/scene.h"

//            char* name, color_t* color, int bc, int lc, label_t* labels, label_t* buttons
scene_t scene(char* name, color_t* color, int bc, int lc, label_t* labels, button_t* buttons) {
  scene_t scene;
  scene.scene_name = name;
  scene.bg_color = *color;
  scene.buttonsc = bc;
  scene.labelsc = lc;
  scene.labels = labels;
  scene.buttons = buttons;
  return scene;
}
