#include "label.h"
#include "color.h"
#include "button.h"

#ifndef __SCENE_H__
#define __SCENE_H__

typedef struct {
  char* scene_name;
  color_t bg_color;
  int buttonsc;
  int labelsc;
  label_t* labels;
  button_t* buttons;
} scene_t;

scene_t scene(char*, color_t*, int, int, label_t*, button_t*);

#endif
