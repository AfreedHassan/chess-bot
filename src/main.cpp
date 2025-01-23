#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <iostream>
#include <process.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;
  SDL_Texture *boardTexture = NULL;
  ;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialise. SDL_Error: " << SDL_GetError()
              << '\n';
  } else {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError()
                << '\n';
    } else {
      SDL_Renderer *renderer = nullptr;
      renderer = SDL_CreateRenderer(window, -1, 0);

      int flags = IMG_INIT_PNG;
      int initStatus = IMG_Init(flags);
      if ((initStatus & flags) != flags) {
        std::cout << "SDL2_Image format not available" << std::endl;
      }


      SDL_Surface *tmpSurface = IMG_Load("assets/chessboard.png");
      boardTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
      tmp
      SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
      SDL_RenderPresent(renderer);
      // SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format,
      // 0xFF, 0x0, 0xFF)); SDL_UpdateWindowSurface(window);
      SDL_Delay(3 * 1000);
    }
  }

  return 0;
}
