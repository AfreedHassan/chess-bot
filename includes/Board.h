#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <string>

using ColorType = char;
using PieceType = std::string;

class Board {
  uint64_t pieceBB[14];
  uint64_t emptyBB;
  uint64_t occupiedBB;

public:
  enum enumPiece {
    nWhite,
    nBlack,
    nWhitePawn,
    nBlackPawn,
    nWhiteBishop,
    nBlackBishop,
    nWhiteKnight,
    nBlackKnight,
    nWhiteRook,
    nBlackRook,
    nWhiteQueen,
    nBlackQueen,
    nWhiteKing,
    nBlackKing
  };

  uint64_t getPieceSet(PieceType &&pt) const;
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
  uint8_t getPieceIndex(PieceType pt) const;
  void setOccupied();
  void setEmpty();
  void showOccupied() const;
  void showBitboard(uint64_t bb) const;
  Board();
};

#endif // !BOARD_H
