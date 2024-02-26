#include "label.h"
#include "color.h"
#include "button.h"
#include "scrollview.h"

#ifndef __SCENE_H__
#define __SCENE_H__

// union of all the types that can be held inside the special views inside of scene
typedef union {
  scrollview_t scrollview;
} special_view_u;

typedef struct {
  char* scene_name;
  color_t bg_color;
  int buttonsc;
  int labelsc;
  int special_viewsc;
  label_t* labels;
  button_t* buttons;
  special_view_u* special_views;
} scene_t;

scene_t scene(char*, color_t*, int, int, int, label_t*, button_t*, special_view_u*);

#endif
