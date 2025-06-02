#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <iostream>
#include <process.h>

struct RGB_COLOR_ {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB_COLOR_;

void drawBoardFromImage(SDL_Renderer *renderer);

void drawBoard(SDL_Renderer *renderer);

// Screen dimension constants
// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 660;
const int SCREEN_HEIGHT = 660;
int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Surface *screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialise. SDL_Error: " << SDL_GetError()
              << '\n';
  } else {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
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
      drawBoard(renderer);

      // SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format,
      // 0xFF, 0x0, 0xFF)); SDL_UpdateWindowSurface(window);
      SDL_Delay(3 * 1000);

      // quit
      SDL_Quit();
    }
  }

  return 0;
}
void drawBoardFromImage(SDL_Renderer *renderer) {
  SDL_Texture *boardTexture = NULL;
  SDL_Surface *tmpSurface = IMG_Load("assets/chessboard.png");
  boardTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void drawBoard(SDL_Renderer *renderer) {
  SDL_RenderClear(renderer);

  // LIGHT_BROWN = rgba(241,217,181,255)
  // DARK_BROWN = rgba(181,136,99,255)
  struct RGB_COLOR_ LIGHT_SQUARE = {241, 217, 181};
  struct RGB_COLOR_ DARK_SQUARE = {181, 136, 99};

  int rows = 8, cols = 8, squareLength = 80, spacing = 0;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      SDL_Rect rect;
      rect.x = 10 + col * (squareLength + spacing);
      rect.y = 10 + row * (squareLength + spacing);
      rect.w = squareLength;
      rect.h = squareLength;

      if ((row + col) & 1) {
        SDL_SetRenderDrawColor(renderer, LIGHT_SQUARE.r, LIGHT_SQUARE.g,
                               LIGHT_SQUARE.b, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, DARK_SQUARE.r, DARK_SQUARE.g,
                               DARK_SQUARE.b, 255);
      }
      SDL_RenderFillRect(renderer, &rect);
    }
  }
  SDL_RenderPresent(renderer);
}
