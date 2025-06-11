#include "../includes/BoardView.h"
#include <filesystem>
#include <iostream>
#include <map>

BoardView::BoardView() : window_(NULL), renderer_(nullptr) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialise. SDL_Error: " << SDL_GetError()
              << '\n';
  } else {
    window_ = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window_ == NULL) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError()
                << '\n';
    } else {
      renderer_ = SDL_CreateRenderer(window_, -1, 0);

      int flags = IMG_INIT_PNG;
      int initStatus = IMG_Init(flags);
      if ((initStatus & flags) != flags) {
        std::cout << "SDL2_Image format not available" << std::endl;
      }
    }
  }
  this->drawBoard();
  this->drawPieces();
  SDL_RenderPresent(renderer_);

  SDL_Delay(5 * 1000);
}

BoardView::~BoardView() { SDL_Quit(); }

void BoardView::drawBoard() {
  SDL_RenderClear(renderer_);

  // LIGHT_BROWN = rgba(241,217,181,255)
  // DARK_BROWN = rgba(181,136,99,255)
  struct BoardView::SQUARE_COLOR_ LIGHT_SQUARE = {241, 217, 181};
  struct BoardView::SQUARE_COLOR_ DARK_SQUARE = {181, 136, 99};

  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      SDL_Rect rect;
      rect.x = 10 + col * (SQUARELENGTH + SPACING);
      rect.y = 10 + row * (SQUARELENGTH + SPACING);
      rect.w = SQUARELENGTH;
      rect.h = SQUARELENGTH;

      if ((row + col) & 1) {
        SDL_SetRenderDrawColor(renderer_, LIGHT_SQUARE.r, LIGHT_SQUARE.g,
                               LIGHT_SQUARE.b, 255);
      } else {
        SDL_SetRenderDrawColor(renderer_, DARK_SQUARE.r, DARK_SQUARE.g,
                               DARK_SQUARE.b, 255);
      }
      SDL_RenderFillRect(renderer_, &rect);
    }
  }
}

void BoardView::drawPieces() {
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
    this->drawPieceAtSquare("wR", fileIndex, rankIndex);
    x &= x - 1; // Clear the lowest set bit
  }

  /*drawPieceAtSquare(renderer_, "bR", 0, 7);*/
  /*drawPieceAtSquare(renderer_, "bN", 1, 7);*/
  /*drawPieceAtSquare(renderer_, "bB", 2, 7);*/
  /*drawPieceAtSquare(renderer_, "bQ", 3, 7);*/
  /*drawPieceAtSquare(renderer_, "bK", 4, 7);*/
  /*drawPieceAtSquare(renderer_, "bB", 5, 7);*/
  /*drawPieceAtSquare(renderer_, "bN", 6, 7);*/
  /*drawPieceAtSquare(renderer_, "bR", 7, 7);*/
  /*for (short int file = 0; file < 8; file++) {*/
  /*  drawPieceAtSquare(renderer_, "bP", file, 6);*/
  /*}*/
  /*drawPieceAtSquare(renderer_, "wR", 0, 0);*/
  /*drawPieceAtSquare(renderer_, "wN", 1, 0);*/
  /*drawPieceAtSquare(renderer_, "wB", 2, 0);*/
  /*drawPieceAtSquare(renderer_, "wQ", 3, 0);*/
  /*drawPieceAtSquare(renderer_, "wK", 4, 0);*/
  /*drawPieceAtSquare(renderer_, "wB", 5, 0);*/
  /*drawPieceAtSquare(renderer_, "wN", 6, 0);*/
  /*drawPieceAtSquare(renderer_, "wR", 7, 0);*/
  /*for (short int file = 0; file < 8; file++) {*/
  /*  drawPieceAtSquare(renderer_, "wP", file, 1);*/
  /*}*/
}

void BoardView::drawPieceAtSquare(std::string &&piece, uint8_t file,
                                  uint8_t rank) {
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
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);

  SDL_Rect rect;
  rect.x = 10 + col * (SQUARELENGTH + SPACING);
  rect.y = 10 + row * (SQUARELENGTH + SPACING);
  rect.h = SQUARELENGTH;
  rect.w = SQUARELENGTH;
  SDL_RenderCopy(renderer_, texture, NULL, &rect);
}
