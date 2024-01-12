#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SDL_MAIN_HANDLED

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 850

typedef struct {
  int r;
  int g;
  int b;
} Color;

typedef struct {
  bool quit;
} GameState;

enum COLOR {
  RED, 
  BLUE,
  GREEN
};

enum COLOR toggleColor(enum COLOR);
Color getColorValues(enum COLOR);
Color createColor(int, int, int);
Color getCurrent(Color*, int);
void handleKeyInput(GameState*, int);

int main(int argc, char* argv[]) {
  SDL_Window*      win = NULL;
  SDL_Renderer*    ren = NULL;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &win, &ren);

  
  bool KEYS[322];  // 322 is the number of SDLK_DOWN events
      
  for(int i = 0; i < 322; i++) { // init them all to false
      KEYS[i] = false;
  }
      
  // SDL_EnableKeyRepeat(0, 0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down


  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);
  GameState gs;
  gs.quit = false;

  int currentIndex = 0;
  Color carousel[3];
  carousel[0] = createColor(255, 0, 0);
  carousel[1] = createColor(0, 255, 0);
  carousel[2] = createColor(0, 0, 255);

  Color currentColor = carousel[currentIndex];
  SDL_SetRenderDrawColor(ren, currentColor.r, currentColor.g, currentColor.b, 255);

  // Event handler
  SDL_Event e;

  
  // While application is running
  while (!gs.quit) {
     // Handle events on queue
     while (SDL_PollEvent( &e ) != 0) { // poll for event
        // User requests quit
        switch (e.type) {
            case SDL_QUIT: // unless player manually quits
              gs.quit = true;
            case SDL_MOUSEBUTTONDOWN:
              currentIndex++;
              currentColor = getCurrent(&carousel, currentIndex);
              SDL_SetRenderDrawColor(ren, currentColor.r, currentColor.g, currentColor.b, 255);
            case SDL_KEYDOWN:
              handleKeyInput(&gs, e.key.keysym.sym);
        }
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);
     }
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}

Color getCurrent(Color* carousel, int index) {
  return carousel[index % 3];
}

Color getColorValues(enum COLOR c) {
  Color cValues;
  switch (c) {
    case RED:
      cValues = createColor(255, 0, 0);
    case BLUE:
      cValues = createColor(0, 0, 255);
    case GREEN:
      cValues = createColor(0, 255, 0);
  }
  return cValues;
}

enum COLOR toggleColor(enum COLOR c) {
  switch (c) {
    case RED:
      return BLUE;
    case BLUE:
      return GREEN;
    case GREEN:
      return RED;
  }
}

Color createColor(int r, int g, int b) {
  Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}

void handleKeyInput(GameState* gsPtr, int input) {
  switch (input) {
    case SDLK_q:
      gsPtr->quit = true;
  }
}
