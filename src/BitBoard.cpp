#include "../includes/BitBoard.h"

BitBoard::BitBoard() : pieceType_(""), bitboard_(0) {}

BitBoard::BitBoard(std::string &pieceType, uint64_t &bitboard)
    : pieceType_(pieceType), bitboard_(bitboard) {}

BitBoard::BitBoard(std::string &&pieceType, uint64_t &&bitboard)
    : pieceType_(pieceType), bitboard_(bitboard) {}

std::string BitBoard::getPieceType() { return this->pieceType_; }

uint64_t BitBoard::getBitBoard() { return this->bitboard_; }

void BitBoard::setPieceType(std::string &pieceType) {
  this->pieceType_ = pieceType;
}
void BitBoard::setPieceType(std::string &&pieceType) {
  this->pieceType_ = pieceType;
}
void BitBoard::setBitBoard(uint64_t &bitboard) { this->bitboard_ = bitboard; }
void BitBoard::setBitBoard(uint64_t &&bitboard) { this->bitboard_ = bitboard; }
