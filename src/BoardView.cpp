#include "../includes/BoardView.h"
#include <bitset>
#include <filesystem>
#include <iostream>
#include <map>

BoardView::BoardView(Board *board)
    : window_(NULL), renderer_(nullptr), board_(board) {
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

      // initialise textures
      for (uint8_t i = 0; i < Piece::PIECE_CODE_COUNT; i++) {
        std::string imgPath = "assets/pieces/" + pieceImgFileNames_[i];
        SDL_Surface *surface = IMG_Load(imgPath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
        SDL_FreeSurface(surface);
        pieceTextures_[i] = texture;
      }
    }
  }
  this->drawBoard();
  SDL_RenderCopy(renderer_, boardTexture_, NULL, NULL);
  this->drawPieces();
  SDL_RenderPresent(renderer_);

  SDL_Event event;
  SDL_Texture *pieceTexture = nullptr;
  uint8_t rank = 255, file = 255;
  bool run = 1, isPieceInHand = 0;

  while (run) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        run = 0;
      }

      if (event.type == SDL_MOUSEBUTTONUP) {
        SDL_Log("EVENT: LMB released. Piece dragging stopped.");
        pieceTexture = nullptr;
        isPieceInHand = 0;

        if (!boardTexture_) {
          SDL_Log("boardTexture_ is null!");
        }
        // main drawing loop
        SDL_RenderClear(renderer_);
        // draw the base layer first containing the board texture
        SDL_RenderCopy(renderer_, boardTexture_, NULL, NULL);
        // draw the pieces
        this->drawPieces();
        SDL_RenderPresent(renderer_);
      }
      // OPTIONS:
      //   1: Click on empty square -> do nothing
      //   2: Click on occupied square -> see following options
      // 2.1: DRAG PIECE -> draw board, pieces, blank piece square.
      // 2.2: STOP DRAGGING PIECE -> draw board, pieces and piece square

      // MOUSE being moved while LEFTMOUSEBUTTON DOWN
      if (event.type == SDL_MOUSEMOTION && event.motion.state & SDL_BUTTON_LMASK) {
        printf("X: %d, Y: %d\n", event.button.x, event.button.y);
        if (event.button.x > 10 && event.button.x < ROWS * SQUARELENGTH + 10 &&
            event.button.y > 10 && event.button.y < COLS * SQUARELENGTH + 10) {

          SDL_Rect pieceRect;
          pieceRect.x = event.button.x - (SQUARELENGTH >> 1);
          pieceRect.y = event.button.y - (SQUARELENGTH >> 1);
          pieceRect.h = SQUARELENGTH;
          pieceRect.w = SQUARELENGTH;

          if (!boardTexture_) {
            SDL_Log("boardTexture_ is null!");
          }
          // main drawing loop
          SDL_RenderClear(renderer_);
          // draw the base layer first containing the board texture
          SDL_RenderCopy(renderer_, boardTexture_, NULL, NULL);
          // draw the pieces
          this->drawPieces();

          SDL_Log("Piece being dragged.");

          // if !isPieceInHand: new piece being taken in hand.
          if (!isPieceInHand) {
            // get rank,file of new piece
            std::tie(rank, file) = this->getRankAndFileFromCoordinates(event.button.x, event.button.y);
            // get texture of new piece
            Piece::PieceCode pc = board_->getPieceAt(rank, file);
            std::cout << "PieceCode: " << std::bitset<4>(pc) << '\n';
            pieceTexture = getPieceTexture(pc);

            isPieceInHand = 1; // since new piece is now in hand.
          }
          this->clearSquare(rank, file);
          SDL_RenderCopy(renderer_, pieceTexture, NULL, &pieceRect);

          /*printf("rank: %d, file: %d\n", rank, file);*/
          SDL_RenderPresent(renderer_);
        }
      }
    }
  }
}

BoardView::~BoardView() { SDL_Quit(); }

void BoardView::drawBoard() {
  boardTexture_ =
      SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

  SDL_SetRenderTarget(renderer_, boardTexture_);
  SDL_RenderClear(renderer_);

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
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_SetRenderTarget(renderer_, nullptr);
}

void BoardView::drawPieces() {
  for (uint8_t pieceCode = Piece::epcWhitePawn; pieceCode < Piece::PIECE_CODE_COUNT; pieceCode++) {
    uint64_t bb = this->board_->getPieceSet(pieceCode);
    while (bb) {
      int squareIndex = __builtin_ctzll(bb); // Count trailing zeros
      uint8_t fileIndex = squareIndex & 7;
      uint8_t rankIndex = squareIndex >> 3;
      this->drawPieceAtSquare(static_cast<Piece::PieceCode>(pieceCode), fileIndex, rankIndex);
      bb &= bb - 1; // Clear the lowest set bit
    }
  }
}

void BoardView::drawPieceAtSquare(Piece::PieceCode pc, uint8_t file,
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
  /*SDL_Surface *surface = IMG_LoadSVG_RW(SDL_RWFromFile(imgPath.c_str(),
   * "rb"));*/

  /*SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");*/
  SDL_Rect rect;
  rect.x = 10 + col * (SQUARELENGTH + SPACING);
  rect.y = 10 + row * (SQUARELENGTH + SPACING);
  rect.h = SQUARELENGTH;
  rect.w = SQUARELENGTH;
  SDL_RenderCopy(renderer_, getPieceTexture(pc), NULL, &rect);
}

std::tuple<uint8_t, uint8_t> BoardView::getRankAndFileFromCoordinates(int x,
                                                                      int y) {
  // rect.x = 10 + col * (SQUARELENGTH + SPACING);
  // col * (SQUARELENGTH + SPACING) = rect.x - 10;
  // col = (rext.x-10) / (SQUARELENGTH + SPACING);
  // row = (rext.y-10) / (SQUARELENGTH + SPACING);
  uint8_t row, col;
  row = (y - 10) / (SQUARELENGTH + SPACING);
  col = (x - 10) / (SQUARELENGTH + SPACING);
  // rank = 7 - row, file = col;
  return std::make_tuple(7 - row, col);
}

SDL_Texture *BoardView::getPieceTexture(PieceCode pc) {
  /*std::cout << "getPieceTexture()\n";*/
  if (pc < 0 || pc > Piece::PIECE_CODE_COUNT) {
    std::cerr << "Invalid Piece Code.\n";
    return NULL;
  }
  std::cout << static_cast<uint8_t>(pc) << '\n';
  std::cout << this->pieceImgFileNames_[pc] << '\n';
  return this->pieceTextures_[pc];
}

void BoardView::clearSquare(uint8_t rank, uint8_t file) {
  // row = 7 - rank, col = file;
  uint8_t row = 7 - rank, col = file;
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
