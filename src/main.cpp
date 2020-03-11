#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "voiture.h"
#include "point.h"
#include "map.h"
using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SDL_Window* window = NULL;  //initialize to null to setup renderer and textures before first display
SDL_Renderer *renderer = NULL;

int main(int argc, char* args[]) {

  srand(110);
  Map m(10, 100,100);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());return 1;}
  if (IMG_Init(IMG_INIT_JPG) < 0) {fprintf(stderr, "could not initialize sdl2_image: %s\n", SDL_GetError());return 1;}

  window = SDL_CreateWindow("POM",
                			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                			    SCREEN_WIDTH, SCREEN_HEIGHT,
                			    SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture* texBackground = IMG_LoadTexture(renderer,"../data/grass.JPG");  //Load in GPU
  SDL_Rect rectBackground = { 5, 5, 500, 500 };

  SDL_Event event;

  if (window == NULL) {fprintf(stderr, "could not create window: %s\n", SDL_GetError());return 1;}
  SDL_SetRenderDrawColor(renderer,0,0,0,255);

  bool quit = false;
  while(!quit){
    SDL_PollEvent(&event);  // Récupération des actions de l'utilisateur

    SDL_RenderCopy(renderer, texBackground, NULL, &rectBackground);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    //printf("SDL : %s\n", SDL_GetError());

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
  SDL_DestroyTexture(texBackground);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
