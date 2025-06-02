#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <string>

class BitBoard {
  std::string pieceType;
  uint64_t bitboard;

public:
  BitBoard();
  ~BitBoard();
};

#endif // BITBOARD_H
