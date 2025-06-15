#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "Board.h"
#include "Piece.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <array>
#include <cstdint>

using PieceCode = Piece::PieceCode;

class BoardView {
  // Screen dimension constants
  // const int SCREEN_WIDTH = 640;
  // const int SCREEN_HEIGHT = 480;
  static constexpr uint16_t SCREEN_WIDTH = 660;
  static constexpr uint16_t SCREEN_HEIGHT = 660;
  static constexpr uint8_t ROWS = 8, COLS = 8, SQUARELENGTH = 80, SPACING = 0;

  SDL_Window *window_ = NULL;
  SDL_Renderer *renderer_ = NULL;
  SDL_Texture *boardTexture_ = NULL;
  Board *board_ = NULL;

  std::array<std::string, static_cast<uint8_t>(PieceCode::PIECE_CODE_COUNT)>
      pieceImgFileNames_ = {
          "",
          "",
          "wP.png",
          "bP.png",
          "wB.png",
          "bB.png",
          "wN.png",
          "bN.png",
          "wR.png",
          "bR.png",
          "wQ.png",
          "bQ.png",
          "wK.png",
          "bK.png",
  };
  std::array<SDL_Texture *, 14> pieceTextures_{};

public:
  BoardView();
  BoardView(Board *board);
  ~BoardView();

  struct SQUARE_COLOR_ {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  } RGB_COLOR_;

  // LIGHT_BROWN = rgba(241,217,181,255)
  // DARK_BROWN = rgba(181,136,99,255)
  struct BoardView::SQUARE_COLOR_ LIGHT_SQUARE = {241, 217, 181};
  struct BoardView::SQUARE_COLOR_ DARK_SQUARE = {181, 136, 99};

  void updateBoard(Board *board);
  void drawBoard();
  void drawPieces();
  void drawPieceAtSquare(Piece::PieceCode pc, uint8_t file, uint8_t rank);
  void clearSquare(uint8_t rank, uint8_t file);

  std::tuple<uint8_t, uint8_t> getRankAndFileFromCoordinates(int x, int y);
  SDL_Texture *getPieceTexture(PieceCode pt);
};

#endif // !BOARDVIEW_H
