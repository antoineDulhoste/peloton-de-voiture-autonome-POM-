#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "voiture.h"
#include "point.h"
#include "map.h"
using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {
  char nom[]="route";
  Point p(true,nom);
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  SDL_Event event;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  window = SDL_CreateWindow(
			    "POM",
			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH, SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN
			    );
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  screenSurface = SDL_GetWindowSurface(window);

  bool quit = false;
  while(!quit){
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_PollEvent(&event);  // Récupération des actions de l'utilisateur
    switch(event.type){
        case SDL_QUIT: // Clic sur la croix
            quit=1;
            break;
        case SDL_KEYUP: // Relâchement d'une touche
            if ( event.key.keysym.sym == SDLK_f ){ // Touche f
              cout<<"F"<<endl;
            }
            break;
    }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
