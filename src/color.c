#include <stdio.h>

#include "../include/color.h"

color_t create_color(int r, int g, int b) {
  color_t color = { .r = r, .g = g, .b = b };
  return color;
}
