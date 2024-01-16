#include <stdio.h>

#include "../include/color.h"

color_t create_color(int r, int g, int b) {
  color_t color = { .r = r, .g = g, .b = b };
  return color;
}

color_t* heap_color(int r, int g, int b) {
  color_t* color = malloc(sizeof(color_t));
  color->r = r;
  color->g = g;
  color->b = b;
  return color;
}
