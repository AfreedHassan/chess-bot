#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "Board.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdint>

class BoardView {
  // Screen dimension constants
  // const int SCREEN_WIDTH = 640;
  // const int SCREEN_HEIGHT = 480;
  static constexpr uint16_t SCREEN_WIDTH = 660;
  static constexpr uint16_t SCREEN_HEIGHT = 660;
  static constexpr uint8_t ROWS = 8, COLS = 8, SQUARELENGTH = 80, SPACING = 0;

  SDL_Window *window_ = NULL;
  SDL_Renderer *renderer_ = NULL;

public:
  BoardView();
  ~BoardView();

  struct SQUARE_COLOR_ {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  } RGB_COLOR_;

  void updateBoard(Board *board);
  void drawBoard();
  void drawPieces();
  void drawPieceAtSquare(std::string &&piece, uint8_t file, uint8_t rank);
};

#endif // !BOARDVIEW_H
