#include "../includes/Board.h"
#include <bitset>
#include <iostream>

uint8_t Board::getPieceIndex(PieceType pt) const {
  if (pt == "wP") {
    return nWhitePawn;
  } else if (pt == "bP") {
    return nBlackPawn;
  } else if (pt == "wB") {
    return nWhiteBishop;
  } else if (pt == "bB") {
    return nBlackBishop;
  } else if (pt == "wN") {
    return nWhiteKnight;
  } else if (pt == "bN") {
    return nBlackKnight;
  } else if (pt == "wR") {
    return nWhiteRook;
  } else if (pt == "bR") {
    return nBlackRook;
  } else if (pt == "wQ") {
    return nWhiteQueen;
  } else if (pt == "bQ") {
    return nBlackQueen;
  } else if (pt == "wK") {
    return nWhiteKing;
  } else if (pt == "bK") {
    return nBlackKing;
  }
  return 0;
}

uint64_t Board::getPieceSet(PieceType &&pt) const {
  return this->pieceBB[this->getPieceIndex(pt)];
};
uint64_t Board::getWhitePawns() const { return this->pieceBB[nWhitePawn]; };
uint64_t Board::getBlackPawns() const { return this->pieceBB[nBlackPawn]; };
uint64_t Board::getWhiteBishops() const { return this->pieceBB[nWhiteBishop]; };
uint64_t Board::getBlackBishops() const { return this->pieceBB[nBlackBishop]; };
uint64_t Board::getWhiteKnights() const { return this->pieceBB[nWhiteKnight]; };
uint64_t Board::getBlackKnights() const { return this->pieceBB[nBlackKnight]; };
uint64_t Board::getWhiteRooks() const { return this->pieceBB[nWhiteRook]; };
uint64_t Board::getBlackRooks() const { return this->pieceBB[nBlackRook]; };
uint64_t Board::getWhiteQueens() const { return this->pieceBB[nWhiteQueen]; };
uint64_t Board::getBlackQueens() const {
  return this->pieceBB[enumPiece::nBlackQueen];
};
uint64_t Board::getWhiteKings() const { return this->pieceBB[nWhiteKing]; };
uint64_t Board::getBlackKings() const { return this->pieceBB[nBlackKing]; };
uint64_t Board::getEmpty() const { return this->emptyBB; };
uint64_t Board::getOccupied() const { return this->occupiedBB; };
uint64_t Board::getPawns(ColorType ct) const {
  bool nColor = (ct == 'b');
  return this->pieceBB[nWhitePawn + nColor];
};
uint64_t Board::getBishops(ColorType ct) const {
  bool nColor = (ct == 'b');
  return this->pieceBB[nWhiteBishop + nColor];
};
uint64_t Board::getKnights(ColorType ct) const {
  bool nColor = (ct == 'b');
  return this->pieceBB[nWhiteKnight + nColor];
};
uint64_t Board::getRooks(ColorType ct) const {
  bool nColor = (ct == 'b');
  return this->pieceBB[nWhiteRook + nColor];
};
uint64_t Board::getQueens(ColorType ct) const {
  bool nColor = (ct == 'b');
  return this->pieceBB[nWhiteQueen + nColor];
};
uint64_t Board::getKings(ColorType ct) const {
  bool nColor = (ct == 'b');
  return this->pieceBB[nWhiteKing + nColor];
};

void Board::setOccupied() {
  this->occupiedBB = this->pieceBB[nWhite] | this->pieceBB[nBlack];
}

void Board::setEmpty() { this->emptyBB = ~this->occupiedBB; }

void Board::showBitboard(uint64_t bb) const {
  std::bitset<64> bits(bb);
  for (int row = 7; row >= 0; row--) {
    for (int col = 0; col < 8; col++) {
      std::cout << bits[row * 8 + col] << ' ';
    }
    std::cout << '\n';
  }
}

void Board::showOccupied() const { this->showBitboard(occupiedBB); }

Board::Board() {
  const uint64_t initialBlackPawns = 0x00ff000000000000ULL;
  const uint64_t initialWhitePawns = 0x000000000000ff00ULL;

  const uint64_t initialWhiteBishops = 0x0000000000000024;
  const uint64_t initialBlackBishops = 0x2400000000000000;

  const uint64_t initialWhiteKnights = 0x0000000000000042;
  const uint64_t initialBlackKnights = 0x4200000000000000;

  const uint64_t initialWhiteRooks = 0x0000000000000081;
  const uint64_t initialBlackRooks = 0x8100000000000000;

  const uint64_t initialWhiteQueens = 0x0000000000000008;
  const uint64_t initialBlackQueens = 0x0800000000000000;

  const uint64_t initialWhiteKing = 0x0000000000000010;
  const uint64_t initialBlackKing = 0x1000000000000000;

  this->pieceBB[nWhitePawn] = initialWhitePawns;
  this->pieceBB[nBlackPawn] = initialBlackPawns;
  this->pieceBB[nWhiteBishop] = initialWhiteBishops;
  this->pieceBB[nBlackBishop] = initialBlackBishops;
  this->pieceBB[nWhiteKnight] = initialWhiteKnights;
  this->pieceBB[nBlackKnight] = initialBlackKnights;
  this->pieceBB[nWhiteRook] = initialWhiteRooks;
  this->pieceBB[nBlackRook] = initialBlackRooks;
  this->pieceBB[nWhiteQueen] = initialWhiteQueens;
  this->pieceBB[nBlackQueen] = initialBlackQueens;
  this->pieceBB[nWhiteKing] = initialWhiteKing;
  this->pieceBB[nBlackKing] = initialBlackKing;

  this->pieceBB[nWhite] = initialWhitePawns | initialWhiteBishops |
                          initialWhiteKnights | initialWhiteRooks |
                          initialWhiteQueens | initialWhiteKing;
  this->pieceBB[nBlack] = initialBlackPawns | initialBlackBishops |
                          initialBlackKnights | initialBlackRooks |
                          initialBlackQueens | initialBlackKing;

  this->setOccupied();
  this->setEmpty();
}
