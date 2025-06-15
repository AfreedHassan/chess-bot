#include "../includes/Board.h"
#include <bitset>
#include <iostream>

PieceCode Board::getPieceCode(PieceType pt) const {
  if (pt == "wP") {
    return PieceCode::epcWhitePawn;
  } else if (pt == "bP") {
    return PieceCode::epcBlackPawn;
  } else if (pt == "wB") {
    return PieceCode::epcWhiteBishop;
  } else if (pt == "bB") {
    return PieceCode::epcBlackBishop;
  } else if (pt == "wN") {
    return PieceCode::epcWhiteKnight;
  } else if (pt == "bN") {
    return PieceCode::epcBlackKnight;
  } else if (pt == "wR") {
    return PieceCode::epcWhiteRook;
  } else if (pt == "bR") {
    return PieceCode::epcBlackRook;
  } else if (pt == "wQ") {
    return PieceCode::epcWhiteQueen;
  } else if (pt == "bQ") {
    return PieceCode::epcBlackQueen;
  } else if (pt == "wK") {
    return PieceCode::epcWhiteKing;
  } else if (pt == "bK") {
    return PieceCode::epcBlackKing;
  } else
    return PieceCode::epcWhite;
}

/*} else if (pt == "bP") {*/
/*  return PieceCode::epcBlackPawn;*/
/*} else if (pt == "wB") {*/
/*  return PieceCode::epcWhiteBishop;*/
/*} else if (pt == "bB") {*/
/*  return PieceCode::epcBlackBishop;*/
/*} else if (pt == "wN") {*/
/*  return PieceCode::epcWhiteKnight;*/
/*} else if (pt == "bN") {*/
/*  return PieceCode::epcBlackKnight;*/
/*} else if (pt == "wR") {*/
/*  return PieceCode::epcWhiteRook;*/
/*} else if (pt == "bR") {*/
/*  return PieceCode::epcBlackRook;*/
/*} else if (pt == "wQ") {*/
/*  return PieceCode::epcWhiteQueen;*/
/*} else if (pt == "bQ") {*/
/*  return PieceCode::epcBlackQueen;*/
/*} else if (pt == "wK") {*/
/*  return PieceCode::epcWhiteKing;*/
/*} else if (pt == "bK") {*/
/*  return PieceCode::epcBlackKing;*/
/*}*/
/*return 0;*/

uint64_t Board::getPieceSet(PieceType &&pt) const {
  return this->pieceBB[this->getPieceCode(pt)];
};

uint64_t Board::getPieceSet(PieceCode &pc) const {
  return this->pieceBB[pc];
};
uint64_t Board::getPieceSet(uint8_t &pc) const {
  return this->pieceBB[pc];
};

/*uint64_t Board::getWhitePawns() const { return
 * this->pieceBB[PieceCode::epcWhitePawn]; };*/
/*uint64_t Board::getBlackPawns() const { return
 * this->pieceBB[PieceCode::epcBlackPawn]; };*/
/*uint64_t Board::getWhiteBishops() const { return
 * this->pieceBB[PieceCode::epcWhiteBishop];
 * };*/
/*uint64_t Board::getBlackBishops() const { return
 * this->pieceBB[PieceCode::epcBlackBishop];
 * };*/
/*uint64_t Board::getWhiteKnights() const { return
 * this->pieceBB[PieceCode::epcWhiteKnight];
 * };*/
/*uint64_t Board::getBlackKnights() const { return
 * this->pieceBB[PieceCode::epcBlackKnight];
 * };*/
/*uint64_t Board::getWhiteRooks() const { return
 * this->pieceBB[PieceCode::epcWhiteRook]; };*/
/*uint64_t Board::getBlackRooks() const { return
 * this->pieceBB[PieceCode::epcBlackRook]; };*/
/*uint64_t Board::getWhiteQueens() const { return
 * this->pieceBB[PieceCode::epcWhiteQueen];
 * };*/
uint64_t Board::getWhitePawns() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhitePawn)];
};
uint64_t Board::getBlackPawns() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackPawn)];
};
uint64_t Board::getWhiteBishops() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteBishop)];
};
uint64_t Board::getBlackBishops() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackBishop)];
};
uint64_t Board::getWhiteKnights() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteKnight)];
};
uint64_t Board::getBlackKnights() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackKnight)];
};
uint64_t Board::getWhiteRooks() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteRook)];
};
uint64_t Board::getBlackRooks() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackRook)];
};
uint64_t Board::getWhiteQueens() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteQueen)];
};
uint64_t Board::getBlackQueens() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackQueen)];
};
uint64_t Board::getWhiteKings() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteKing)];
};
uint64_t Board::getBlackKings() const {
  return this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackKing)];
};
uint64_t Board::getEmpty() const { return this->emptyBB; };
uint64_t Board::getOccupied() const { return this->occupiedBB; };

/*uint64_t Board::getPawns(ColorType ct) const {*/
/*  bool nColor = (ct == 'b');*/
/*  return this->pieceBB[PieceCode::epcWhitePawn + nColor];*/
/*};*/
/*uint64_t Board::getBishops(ColorType ct) const {*/
/*  bool nColor = (ct == 'b');*/
/*  return this->pieceBB[PieceCode::epcWhiteBishop + nColor];*/
/*};*/
/*uint64_t Board::getKnights(ColorType ct) const {*/
/*  bool nColor = (ct == 'b');*/
/*  return this->pieceBB[PieceCode::epcWhiteKnight + nColor];*/
/*};*/
/*uint64_t Board::getRooks(ColorType ct) const {*/
/*  bool nColor = (ct == 'b');*/
/*  return this->pieceBB[PieceCode::epcWhiteRook + nColor];*/
/*};*/
/*uint64_t Board::getQueens(ColorType ct) const {*/
/*  bool nColor = (ct == 'b');*/
/*  return this->pieceBB[PieceCode::epcWhiteQueen + nColor];*/
/*};*/
/*uint64_t Board::getKings(ColorType ct) const {*/
/*  bool nColor = (ct == 'b');*/
/*  return this->pieceBB[PieceCode::epcWhiteKing + nColor];*/
/*};*/

void Board::setOccupied() {
  this->occupiedBB = this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhite)] |
                     this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlack)];
}

void Board::setEmpty() { this->emptyBB = ~this->occupiedBB; }

void Board::showBitboard(uint64_t bb) const {
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

  this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhitePawn)] =
      initialWhitePawns;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackPawn)] =
      initialBlackPawns;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteBishop)] =
      initialWhiteBishops;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackBishop)] =
      initialBlackBishops;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteKnight)] =
      initialWhiteKnights;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackKnight)] =
      initialBlackKnights;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteRook)] =
      initialWhiteRooks;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackRook)] =
      initialBlackRooks;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteQueen)] =
      initialWhiteQueens;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackQueen)] =
      initialBlackQueens;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcWhiteKing)] =
      initialWhiteKing;
  this->pieceBB[static_cast<uint8_t>(PieceCode::epcBlackKing)] =
      initialBlackKing;

  this->pieceBB[PieceCode::epcWhite] =
      initialWhitePawns | initialWhiteBishops | initialWhiteKnights |
      initialWhiteRooks | initialWhiteQueens | initialWhiteKing;

  this->pieceBB[PieceCode::epcBlack] =
      initialBlackPawns | initialBlackBishops | initialBlackKnights |
      initialBlackRooks | initialBlackQueens | initialBlackKing;

  this->showBitboard(this->pieceBB[PieceCode::epcWhite]);

  this->setOccupied();
  this->setEmpty();
}

Piece::PieceCode Board::getPieceAt(uint8_t rank, uint8_t file) {
  // convert rank, file to index in bitset
  /*printf("index: %d\n", ((rank << 3) + file));*/
  uint64_t bit = 1ULL << ((rank << 3) + file);
  // if not in occupiedBB, return empty
  if (!(occupiedBB & bit))
    return PieceCode::epcWhite;
  /*std::cout << "AND Bitboard\n";*/
  /*this->showBitboard(occupiedBB & bit);*/
  // get color: white = 0, black = 1;
  bool nColor =
      (this->pieceBB[PieceCode::epcBlack] & bit) ? 1 : 0;
  /*printf("Color: %d\n", nColor);*/
  // iterate over corresponding bitboards and return that PieceCode
  for (uint8_t i = Piece::epcWhitePawn; i < Piece::PIECE_CODE_COUNT; i += 2) {
    if (this->pieceBB[i + nColor] & bit) {
      return static_cast<Piece::PieceCode>(i + nColor);
    }
  }
  return PieceCode::epcWhite;
}
