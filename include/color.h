#ifndef __COLOR_H__
#define __COLOR_H__

typedef struct {
  int r;
  int g;
  int b;
} color_t;

color_t create_color(int, int, int);
color_t* heap_color(int, int, int);

#endif
