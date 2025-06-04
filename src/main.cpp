#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <bitset>
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <map>
/*#include <process.h>*/

#include "../includes/Board.h"

struct RGB_COLOR_ {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGB_COLOR_;

void drawBoardFromImage(SDL_Renderer *renderer);

void drawBoard(SDL_Renderer *renderer);

void drawPieces(SDL_Renderer *renderer);

void drawPieceAtSquare(SDL_Renderer *renderer, std::string &&piece,
                       uint8_t file, uint8_t rank);

// Board constants
const int ROWS = 8, COLS = 8, SQUARELENGTH = 80, SPACING = 0;

// Screen dimension constants
// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 660;
const int SCREEN_HEIGHT = 660;

void Game() {
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
      drawPieces(renderer);
      SDL_RenderPresent(renderer);

      // SDL_FillRect( screenSurface, NULL, SDL_MapRGB(screenSurface->format,
      // 0xFF, 0x0, 0xFF)); SDL_UpdateWindowSurface(window);
      SDL_Delay(5 * 1000);

      // quit
      SDL_Quit();
    }
  }
}

void showBitboard(uint64_t bb) {
  std::bitset<64> bits(bb);
  for (int row = 7; row >= 0; row--) {
    for (int col = 0; col < 8; col++) {
      std::cout << bits[row * 8 + col] << ' ';
    }
    std::cout << " | " << row + 1;
    std::cout << '\n';
  }
  std::cout << "- - - - - - - -\n";
  std::cout << "a b c d e f g h\n";
}

void temp() {
  uint64_t bb = 0b10000001ULL; // example bitboard (e.g., knight positions)
  const uint64_t notAFile = 0xfe;
  const uint64_t aFile = 0x0101010101010101;
  const uint64_t hFile = 0x8080808080808080;
  const uint64_t firstRank = 0x00000000000000FF;
  const uint64_t a1toh8Diag = 0x8040201008040201;
  const uint64_t h1toa8AntiDiag = 0x0102040810204080;
  const uint64_t a1h8 =
      0b1000000000000000000000000000000000000000000000000000000000000001ULL;

  const uint64_t initialWhiteRooks = 0x0000000000000081;
  showBitboard(initialWhiteRooks);
}

int main(int argc, char *args[]) { return 0; }

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

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      SDL_Rect rect;
      rect.x = 10 + col * (SQUARELENGTH + SPACING);
      rect.y = 10 + row * (SQUARELENGTH + SPACING);
      rect.w = SQUARELENGTH;
      rect.h = SQUARELENGTH;

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
  /*SDL_RenderPresent(renderer);*/
}

void drawPieces(SDL_Renderer *renderer) {
  std::string path = "assets/pieces";
  std::map<std::string, std::string> piecePaths;

  for (auto &entry : std::filesystem::directory_iterator(path)) {
    if (entry.path().extension() == ".png") {
      piecePaths[entry.path().filename()] = entry.path();
    }
  }
  Board *board = new Board();
  uint64_t x = board->getWhiteRooks();
  while (x) {
    int squareIndex = __builtin_ctzll(x); // Count trailing zeros
    printf("Square Index : %d\n", squareIndex);
    uint8_t fileIndex = squareIndex & 7;
    uint8_t rankIndex = squareIndex >> 3;
    printf("FileIndex: %d, RankIndex : %d\n", fileIndex, rankIndex);
    drawPieceAtSquare(renderer, "wR", fileIndex, rankIndex);
    x &= x - 1; // Clear the lowest set bit
  }

  /*drawPieceAtSquare(renderer, "bR", 0, 7);*/
  /*drawPieceAtSquare(renderer, "bN", 1, 7);*/
  /*drawPieceAtSquare(renderer, "bB", 2, 7);*/
  /*drawPieceAtSquare(renderer, "bQ", 3, 7);*/
  /*drawPieceAtSquare(renderer, "bK", 4, 7);*/
  /*drawPieceAtSquare(renderer, "bB", 5, 7);*/
  /*drawPieceAtSquare(renderer, "bN", 6, 7);*/
  /*drawPieceAtSquare(renderer, "bR", 7, 7);*/
  /*for (short int file = 0; file < 8; file++) {*/
  /*  drawPieceAtSquare(renderer, "bP", file, 6);*/
  /*}*/
  /*drawPieceAtSquare(renderer, "wR", 0, 0);*/
  /*drawPieceAtSquare(renderer, "wN", 1, 0);*/
  /*drawPieceAtSquare(renderer, "wB", 2, 0);*/
  /*drawPieceAtSquare(renderer, "wQ", 3, 0);*/
  /*drawPieceAtSquare(renderer, "wK", 4, 0);*/
  /*drawPieceAtSquare(renderer, "wB", 5, 0);*/
  /*drawPieceAtSquare(renderer, "wN", 6, 0);*/
  /*drawPieceAtSquare(renderer, "wR", 7, 0);*/
  /*for (short int file = 0; file < 8; file++) {*/
  /*  drawPieceAtSquare(renderer, "wP", file, 1);*/
  /*}*/
}

void drawPieceAtSquare(SDL_Renderer *renderer, std::string &&piece,
                       uint8_t file, uint8_t rank) {
  // a8 is top left (closest to origin)
  /* a8 - - - - - - - - - h8
   * |                    |
   * |                    |
   * |                    |
   * |                    |
   * |                    |
   * |                    |
   * a1  - - - - - - - -  h1
   */
  uint8_t col = file, row = 7 - rank;
  std::string imgPath = "assets/pieces/" + piece + ".png";
  /*SDL_Surface *surface = IMG_LoadSVG_RW(SDL_RWFromFile(imgPath.c_str(),
   * "rb"));*/

  /*SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");*/
  SDL_Surface *surface = IMG_Load(imgPath.c_str());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  SDL_Rect rect;
  rect.x = 10 + col * (SQUARELENGTH + SPACING);
  rect.y = 10 + row * (SQUARELENGTH + SPACING);
  rect.h = SQUARELENGTH;
  rect.w = SQUARELENGTH;
  SDL_RenderCopy(renderer, texture, NULL, &rect);
}
