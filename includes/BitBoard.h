#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <string>

//  LSF (Least Significant File Mapping)
//  LSF squareIndex = 8 * rankIndex + fileIndex;

// BitBoard
// attribute: pieceType - Type of the piece eg wP for whitePawn etc.
// attribute: bitboard - bitboard for this pieceType

class BitBoard {
  std::string pieceType_;
  uint64_t bitboard_;

public:
  BitBoard();
  BitBoard(std::string &pieceType, uint64_t &bitboard);
  BitBoard(std::string &&pieceType, uint64_t &&bitboard);
  ~BitBoard();
  std::string getPieceType();
  uint64_t getBitBoard();
  void setPieceType(std::string &pieceType);
  void setPieceType(std::string &&pieceType);
  void setBitBoard(uint64_t &bitboard);
  void setBitBoard(uint64_t &&bitboard);
};

#endif // BITBOARD_H
