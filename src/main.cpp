#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_image.h>
#include "voiture.h"
#include "point.h"
#include "map.h"
using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define CIRCLE_SIZE 20

SDL_Window* window = NULL;  //initialize to null to setup renderer and textures before first display
SDL_Renderer *renderer = NULL;

int main(int argc, char* args[]) {
  //srand(93);    //seed random
  std::vector<Point> points;
  points.push_back(Point(0,42,28));
  points.push_back(Point(1,47,9));
  points.push_back(Point(2,76,35));
	points.push_back(Point(3,42,75));
  points.push_back(Point(4,84,65));
  points.push_back(Point(5,8,80));
  points.push_back(Point(6,69,13));
	points.push_back(Point(7,57,52));
  points.push_back(Point(8,63,79));
	points.push_back(Point(9,6,95));
	points.push_back(Point(10,96,59));
	points.push_back(Point(11,27,49));
	points.push_back(Point(12,24,17));
	points.push_back(Point(13,54,94));
	points.push_back(Point(14,18,60));
  Map m(points, 100,100);
  m.setRoute(0, 1);
  m.setRoute(0, 2);
  m.setRoute(0, 3);
  m.setRoute(0, 6);
  m.setRoute(0, 7);
  m.setRoute(0, 11);
  m.setRoute(0, 12);
  m.setRoute(1, 12);
  m.setRoute(1, 6);
  m.setRoute(2, 6);
  m.setRoute(3, 7);
  m.setRoute(3, 8);
  m.setRoute(3, 13);
  m.setRoute(3, 11);
  m.setRoute(3, 14);
  m.setRoute(4, 10);
  m.setRoute(4, 7);
  m.setRoute(4, 8);
  m.setRoute(4, 8);
  m.setRoute(5, 9);
  m.setRoute(5, 14);
  m.setRoute(7, 8);
  m.setRoute(8, 13);
  m.setRoute(11, 14);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());return 1;}
  if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) < 0) {fprintf(stderr, "could not initialize sdl2_image: %s\n", SDL_GetError());return 1;}

  window = SDL_CreateWindow("POM",
                			    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                			    SCREEN_WIDTH, SCREEN_HEIGHT,
                			    SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Texture* texBackground = IMG_LoadTexture(renderer,"../data/grass.JPG");  //Load in GPU
  SDL_Texture* texCircle = IMG_LoadTexture(renderer,"../data/circle.PNG");  //Load in GPU
  SDL_Rect rectBackground = { 0, 0, SCREEN_HEIGHT, SCREEN_HEIGHT };


  SDL_Event event;

  if (window == NULL) {fprintf(stderr, "could not create window: %s\n", SDL_GetError());return 1;}

  bool quit = false;
  while(!quit){
    SDL_PollEvent(&event);  // Récupération des actions de l'utilisateur

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texBackground, NULL, &rectBackground);
    for(unsigned i=0; i<m.getPoints().size();i++){
      for(unsigned j=0; j<m.getPoints().at(i).getDestinations().size(); j++){
        SDL_RenderDrawLine(renderer,
                          m.getPoints().at(i).getX()*SCREEN_HEIGHT/100,
                          m.getPoints().at(i).getY()*SCREEN_HEIGHT/100,
                          m.getPoints().at(m.getPoints().at(i).getDestinations().at(j)).getX()*SCREEN_HEIGHT/100,
                          m.getPoints().at(m.getPoints().at(i).getDestinations().at(j)).getY()*SCREEN_HEIGHT/100
        );
      }
    }

    SDL_Rect rectCircle;
    for(unsigned i=0; i<m.getPoints().size(); i++){
      rectCircle = { m.getPoints().at(i).getX()*SCREEN_HEIGHT/100-CIRCLE_SIZE/2,
                     m.getPoints().at(i).getY()*SCREEN_HEIGHT/100-CIRCLE_SIZE/2,
                     CIRCLE_SIZE, CIRCLE_SIZE};
      SDL_RenderCopy(renderer, texCircle, NULL, &rectCircle);
    }
    SDL_RenderPresent(renderer);
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
  SDL_DestroyTexture(texCircle);
  SDL_DestroyTexture(texBackground);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
