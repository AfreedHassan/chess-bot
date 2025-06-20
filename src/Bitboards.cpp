#include "../includes/Bitboards.h"

#include <iostream>

namespace Bitboards {
uint64_t shiftSouth(uint64_t b) { return b >> 8; }
uint64_t shiftNorth(uint64_t b) { return b << 8; }
uint64_t shiftEast(uint64_t b) { return (b << 1) & notAFile; }
uint64_t shiftWest(uint64_t b) { return (b >> 1) & notHFile; }

uint64_t shiftNortheast(uint64_t b) { return (b << 9) & notAFile; }
uint64_t shiftSoutheast(uint64_t b) { return (b >> 7) & notAFile; }
uint64_t shiftSouthwest(uint64_t b) { return (b >> 9) & notHFile; }
uint64_t shiftNorthwest(uint64_t b) { return (b << 7) & notHFile; }

uint64_t noNoEa(uint64_t b) { return (b << 17) & notAFile; }
uint64_t noEaEa(uint64_t b) { return (b << 10) & notABFile; }
uint64_t soEaEa(uint64_t b) { return (b >> 6) & notABFile; }
uint64_t soSoEa(uint64_t b) { return (b >> 15) & notAFile; }

uint64_t noNoWe(uint64_t b) { return (b << 15) & notHFile; }
uint64_t noWeWe(uint64_t b) { return (b << 6) & notGHFile; }
uint64_t soWeWe(uint64_t b) { return (b >> 10) & notGHFile; }
uint64_t soSoWe(uint64_t b) { return (b >> 17) & notHFile; }

uint64_t fillNorth(uint64_t gen) {
  gen |= (gen << 8);
  gen |= (gen << 16);
  gen |= (gen << 32);
  return gen;
}

uint64_t fillSouth(uint64_t gen) {
  gen |= (gen >> 8);
  gen |= (gen >> 16);
  gen |= (gen >> 32);
  return gen;
}

uint64_t fillEast(uint64_t gen) {
  const uint64_t pr0 = notAFile;
  const uint64_t pr1 = pr0 & (pr0 << 1);
  const uint64_t pr2 = pr1 & (pr1 << 2);
  gen |= pr0 & (gen << 1);
  gen |= pr1 & (gen << 2);
  gen |= pr2 & (gen << 4);
  return gen;
}

uint64_t fillWest(uint64_t gen) {
  const uint64_t pr0 = notHFile;
  const uint64_t pr1 = pr0 & (pr0 >> 1);
  const uint64_t pr2 = pr1 & (pr1 >> 2);
  gen |= pr0 & (gen >> 1);
  gen |= pr1 & (gen >> 2);
  gen |= pr2 & (gen >> 4);
  return gen;
}

uint64_t fillFile(uint64_t gen) {
  return fillNorth(gen) | fillSouth(gen);
}

uint64_t fillRank(uint64_t gen) {
  return fillEast(gen) | fillWest(gen);
}

uint64_t fillNoEa(uint64_t gen) {
  const uint64_t pr0 = notAFile;
  const uint64_t pr1 = pr0 & (pr0 << 9);
  const uint64_t pr2 = pr1 & (pr1 << 18);
  gen |= pr0 & (gen << 9);
  gen |= pr1 & (gen << 18);
  gen |= pr2 & (gen << 36);
  return gen;
}

uint64_t fillSoEe(uint64_t gen) {
  const uint64_t pr0 = notAFile;
  const uint64_t pr1 = pr0 & (pr0 >> 7);
  const uint64_t pr2 = pr1 & (pr1 >> 14);
  gen |= pr0 & (gen >> 7);
  gen |= pr1 & (gen >> 14);
  gen |= pr2 & (gen >> 28);
  return gen;
}

uint64_t fillSoWe(uint64_t gen) {
  const uint64_t pr0 = notHFile;
  const uint64_t pr1 = pr0 & (pr0 >> 9);
  const uint64_t pr2 = pr1 & (pr1 >> 18);
  gen |= pr0 & (gen >> 9);
  gen |= pr1 & (gen >> 18);
  gen |= pr2 & (gen >> 36);
  return gen;
}

uint64_t fillNoWe(uint64_t gen) {
  const uint64_t pr0 = notHFile;
  const uint64_t pr1 = pr0 & (pr0 << 7);
  const uint64_t pr2 = pr1 & (pr1 << 14);
  gen |= pr0 & (gen << 7);
  gen |= pr1 & (gen << 14);
  gen |= pr2 & (gen << 28);
  return gen;
}

uint64_t fillDiag(uint64_t gen) {
  return fillNoEa(gen) | fillSoWe(gen);
}

uint64_t fillAntiDiag(uint64_t gen) {
  return fillSoEe(gen) | fillNoWe(gen);
}

uint64_t wSinglePushTargets(uint64_t wpawns, uint64_t empty) {
  return shiftNorth(wpawns) & empty;
}

uint64_t wDblPushTargets(uint64_t wpawns, uint64_t empty) {
  const uint64_t rank4 = 0x00000000FF000000;
  uint64_t singlePushs = wSinglePushTargets(wpawns, empty);
  return shiftNorth(singlePushs) & empty & rank4;
}

uint64_t bSinglePushTargets(uint64_t bpawns, uint64_t empty) {
  return shiftSouth(bpawns) & empty;
}

uint64_t bDoublePushTargets(uint64_t bpawns, uint64_t empty) {
  const uint64_t rank5 = 0x000000FF00000000;
  uint64_t singlePushs = bSinglePushTargets(bpawns, empty);
  return shiftSouth(singlePushs) & empty & rank5;
}

uint64_t wPawnsAbleToPush(uint64_t wpawns, uint64_t empty) {
  return shiftSouth(empty) & wpawns;
}

uint64_t wPawnsAbleToDoublePush(uint64_t wpawns, uint64_t empty) {
  const uint64_t rank4 = 0x00000000FF000000;
  uint64_t emptyRank3 = shiftSouth(empty & rank4) & empty;
  return wPawnsAbleToPush(wpawns, emptyRank3);
}

uint64_t bPawnsAbleToPush(uint64_t wpawns, uint64_t empty) {
  return shiftNorth(empty) & wpawns;
}

uint64_t bPawnsAbleToDoublePush(uint64_t wpawns, uint64_t empty) {
  const uint64_t rank5 = 0x000000FF00000000;
  uint64_t emptyRank3 = shiftNorth(empty & rank5) & empty;
  return wPawnsAbleToPush(wpawns, emptyRank3);
}

uint64_t getKnightAttacks(uint64_t bb) {
  uint64_t l1 = (bb >> 1) & notHFile;  // shift left
  uint64_t l2 = (bb >> 2) & notGHFile; // double shift left
  uint64_t r1 = (bb << 1) & notAFile;  // shift right
  uint64_t r2 = (bb << 2) & notABFile; // double shift right
  uint64_t h1 = l1 | r1;               // first half
  uint64_t h2 = l2 | r2;               // second half
  // h1 << 16 move up two ranks, h1 >> 16 move down two ranks
  // h2 << 8 move up one rank, h2 >> 8 move down one rank
  return (h1 << 16) | (h1 >> 16) | (h2 << 8) | (h2 >> 8);
}

void initKnightAttacks() {
  for (uint8_t squareIndex = 0; squareIndex < 64; ++squareIndex) {
    arrKnightAttacks[squareIndex] = getKnightAttacks(1ULL << squareIndex);
    std::cout << "Knight attack from square " << squareIndex << '\n';
    showBitboard(arrKnightAttacks[squareIndex]);
  }
}

uint64_t knightFill(uint64_t knights) {
  return getKnightAttacks(knights) | knights;
}

uint64_t getKingAttacks(uint64_t kingSet) {
  uint64_t attacks = shiftEast(kingSet) | shiftWest(kingSet);
  kingSet |= attacks;
  attacks |= shiftNorth(kingSet) | shiftSouth(kingSet);
  return attacks;
}

void initKingAttacks() {
  uint64_t bb = 1ULL;
  for (int sq = 0; sq < 64; sq++, bb <<= 1)
    arrKingAttacks[sq] = getKingAttacks(bb);
}

uint64_t forkTargetSquare(uint64_t targets) {
  uint64_t west, east, attak, forks;
  east = shiftEast(targets); // r1
  west = shiftWest(targets); // l1
  attak = east << 16;        // l1 down two ranks
                             //
  forks = (west << 16) & attak;
  attak |= west << 16;

  forks |= (east >> 16) & attak;
  attak |= east >> 16;

  forks |= (west >> 16) & attak;
  attak |= west >> 16;

  east = shiftEast(east);
  west = shiftWest(west);

  forks |= (east << 8) & attak;
  attak |= east << 8;

  forks |= (west << 8) & attak;
  attak |= west << 8;

  forks |= (east >> 8) & attak;
  attak |= east >> 8;

  forks |= (west >> 8) & attak;

  return forks;
}

// sliding pieces (rook, bishop) stuff.
void getRookOccMask(uint64_t bb) {
  uint64_t occMask = (fillFile(bb) & NotFirstRank & NotEighthRank | fillFile(bb) & notAFile & notHFile) & ~bb;
  showBitboard(occMask);
}

void getBishopOccMask(uint64_t bb) {
  uint64_t occMask = fillDiag(bb) | fillAntiDiag(bb);
  occMask &= notAFile & notHFile & NotFirstRank & NotEighthRank;
  occMask &= ~bb;
  showBitboard(occMask);
}

} // namespace Bitboards
