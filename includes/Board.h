#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <cstdint>
#include <string>

using ColorType = char;
using PieceType = std::string;
using PieceCode = Piece::PieceCode;

class Board {
  uint64_t pieceBB[14];
  uint64_t emptyBB;
  uint64_t occupiedBB;

public:
  // add the binary reps of the enums numbers below
  /*
  enum enumPiece {
    nWhite,       // 0000 (0)
    nBlack,       // 0001 (1)
    nWhitePawn,   // 0010 (2)
    nBlackPawn,   // 0011 (3)
    nWhiteBishop, // 0100 (4)
    nBlackBishop, // 0101 (5)
    nWhiteKnight, // 0110 (6)
    nBlackKnight, // 0111 (7)
    nWhiteRook,   // 1000 (8)
    nBlackRook,   // 1001 (9)
    nWhiteQueen,  // 1010 (10)
    nBlackQueen,  // 1011 (11)
    nWhiteKing,   // 1100 (12)
    nBlackKing    // 1101 (13)
  }; */
  uint64_t getPieceSet(PieceType &&pt) const;
  uint64_t getPieceSet(PieceCode &pt) const;
  uint64_t getPieceSet(uint8_t &pt) const;
  uint64_t getWhitePawns() const;
  uint64_t getBlackPawns() const;
  uint64_t getWhiteBishops() const;
  uint64_t getBlackBishops() const;
  uint64_t getWhiteKnights() const;
  uint64_t getBlackKnights() const;
  uint64_t getWhiteRooks() const;
  uint64_t getBlackRooks() const;
  uint64_t getWhiteQueens() const;
  uint64_t getBlackQueens() const;
  uint64_t getWhiteKings() const;
  uint64_t getBlackKings() const;
  uint64_t getEmpty() const;
  uint64_t getOccupied() const;
  uint64_t getPawns(ColorType ct) const;
  uint64_t getBishops(ColorType ct) const;
  uint64_t getKnights(ColorType ct) const;
  uint64_t getRooks(ColorType ct) const;
  uint64_t getQueens(ColorType ct) const;
  uint64_t getKings(ColorType ct) const;
  void setOccupied();
  void setEmpty();
  void showOccupied() const;
  void showBitboard(uint64_t bb) const;

  PieceCode getPieceAt(uint8_t file, uint8_t rank);
  PieceCode getPieceCode(PieceType pt) const;

  Board();
};

#endif // !BOARD_H
