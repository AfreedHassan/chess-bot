#include "../includes/Bitboards.h"

#include <SDL2/SDL_log.h>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

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

uint64_t calculateKnightAttacks(uint64_t bb) {
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
    arrKnightAttacks[squareIndex] = calculateKnightAttacks(1ULL << squareIndex);
    std::cout << "Knight attack from square " << squareIndex << '\n';
    showBitboard(arrKnightAttacks[squareIndex]);
  }
}

uint64_t knightFill(uint64_t knights) {
  return calculateKnightAttacks(knights) | knights;
}

uint64_t calculateKingAttacks(uint64_t kingSet) {
  uint64_t attacks = shiftEast(kingSet) | shiftWest(kingSet);
  kingSet |= attacks;
  attacks |= shiftNorth(kingSet) | shiftSouth(kingSet);
  return attacks;
}

void initKingAttacks() {
  uint64_t bb = 1ULL;
  for (int sq = 0; sq < 64; sq++, bb <<= 1)
    arrKingAttacks[sq] = calculateKingAttacks(bb);
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
uint64_t calculateRookOccupancyMask(uint64_t bb) {
  uint64_t occMask = (fillFile(bb) & NotFirstRank & NotEighthRank | fillFile(bb) & notAFile & notHFile) & ~bb;
  return occMask;
}

uint64_t calculateBishopOccupancyMask(uint64_t bb) {
  uint64_t occMask = fillDiag(bb) | fillAntiDiag(bb);
  occMask &= notAFile & notHFile & NotFirstRank & NotEighthRank;
  occMask &= ~bb;
  return occMask;
}

/*magic bitboards
* 1.Mask the relevant occupancy bits to form a key. For example if you had a rook on a1, the relevant occupancy bits will be from a2-a7 and b1-g1.
  2. Multiply the key by a "magic number" to obtain an index mapping. This magic number can be generated by brute-force trial and error quite easily although it isn't 100% certain that the magic number is the best possible (see step 3).
  3. Right shift the index mapping by 64-n bits to create an index, where n is the number of bits in the index. A better magic number will have less bits required in the index.
  4. Use the index to reference a preinitialized move database.
*
* 1. occupiedBB = occupiedBB & occupancyMask
* 2. occupiedBB = occupiedBB * magicNum
* 3. occupiedBB = occupiedBB >> nBits // index
* 4. index = occupiedBB;
* bishopAttacks[sq][index]/rookAttacks[sq][index];
*/

uint64_t getBishopAttacks(uint64_t occ, uint8_t sq) {
  uint64_t *aptr = bishopAttacks[sq].ptr;
  occ &= bishopAttacks[sq].mask;
  occ *= bishopAttacks[sq].magic;
  occ >>= bishopAttacks[sq].shift;
  return aptr[occ];
}

uint64_t getRookAttacks(uint64_t occ, uint8_t sq) {
  uint64_t *aptr = rookAttacks[sq].ptr;
  occ &= rookAttacks[sq].mask;
  occ *= rookAttacks[sq].magic;
  occ >>= rookAttacks[sq].shift;
  return aptr[occ];
}

uint64_t random_uint64_t() {
  static std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  return rng();
}

uint64_t random_uint64_t_fewbits() {
  return random_uint64_t() & random_uint64_t() & random_uint64_t() & random_uint64_t();
}

int count1s(uint64_t b) {
  return __builtin_popcountll(b);
  /*int r;*/
  /*for (r = 0; b; r++, b &= b - 1)*/
  /*  ; // Clears LS1B each iteration*/
  /*return r;*/
}

int transformToIndex(uint64_t blockersMask, uint64_t magic, uint8_t bits) {
  return static_cast<int>((blockersMask * magic) >> (64 - bits));
}

int popFirstBit(uint64_t &bb) {
  int index = __builtin_ctzll(bb);
  bb &= bb - 1; // Clear the lowest set bit
  return index;
}

uint64_t permIndexToBlockerMask(int index, int bits, uint64_t mask) {
  int i, j;
  uint64_t result = 0ULL;
  for (i = 0; i < bits; i++) {
    j = popFirstBit(mask); // Get next bit position in mask
    if (index & (1 << i))
      result |= (1ULL << j); // Set that bit if corresponding bit in index is 1
  }
  std::cout << result << '\n';
  return result;
}

uint64_t rookAttacksFromBlocker(uint8_t sqIndex, uint64_t blockersMask, bool showLog = false) {
  uint64_t sqBB = 1ULL << sqIndex;
  uint64_t attack = 0ULL;

  // NORTH
  uint64_t temp = shiftNorth(sqBB);
  if (showLog)
    SDL_Log("Shift north");
  while (temp) {
    attack |= temp;
    if (blockersMask & temp)
      break;
    temp = shiftNorth(temp);
  }

  // SOUTH
  temp = shiftSouth(sqBB);
  if (showLog)
    SDL_Log("Shift south");
  while (temp) {
    attack |= temp;
    if (blockersMask & temp)
      break;
    temp = shiftSouth(temp);
  }

  // EAST
  temp = shiftEast(sqBB);
  if (showLog)
    SDL_Log("Shift east");
  while (temp) {
    attack |= temp;
    if (blockersMask & temp)
      break;
    temp = shiftEast(temp);
  }

  // WEST
  temp = shiftWest(sqBB);
  if (showLog)
    SDL_Log("Shift west");
  while (temp) {
    attack |= temp;
    if (blockersMask & temp)
      break;
    temp = shiftWest(temp);
  }

  if (showLog)
    SDL_Log("Attack bitboard:");
  return attack;
}

uint64_t bishopAttacksFromBlocker(uint8_t sqIndex, uint64_t blockersMask, bool showLog = false) {
  uint64_t sqBB = 1ULL << sqIndex, attack = sqBB, temp;

  temp = shiftNorthwest(sqBB);
  if (showLog)
    SDL_Log("Shift northwest\n");
  while (!(blockersMask & attack) && sqBB) {
    attack |= sqBB;
    sqBB = shiftNorthwest(sqBB);
  }

  sqBB = 1ULL << sqIndex;
  temp = shiftSouthwest(sqBB);
  if (showLog)
    SDL_Log("Shift southwest\n");
  while (!(blockersMask & attack) && sqBB) {
    attack |= sqBB;
    sqBB = shiftSouthwest(sqBB);
  }

  sqBB = 1ULL << sqIndex;
  temp = shiftNortheast(sqBB);
  if (showLog)
    SDL_Log("Shift Northeast\n");
  while (!(blockersMask & attack) && sqBB) {
    attack |= sqBB;
    sqBB = shiftNortheast(sqBB);
  }

  sqBB = 1ULL << sqIndex;
  temp = shiftSoutheast(sqBB);
  if (showLog)
    SDL_Log("Shift Southeast\n");
  while (!(blockersMask & attack) && sqBB) {
    attack |= sqBB;
    sqBB = shiftSoutheast(sqBB);
  }
  if (showLog)
    SDL_Log("Attack bitboard\n");
  return (attack ^ (1ULL << sqIndex));
}

uint64_t findMagic(int sq, uint8_t numBits, bool isBishop, bool showLog = false) {
  uint64_t mask, blockersArr[4096], attackArr[4096], used[4096], generation[4096] = {}, magic;
  int i, j, genNumber, n, fail;
  std::string piece = isBishop ? "Bishop" : "Rook";

  mask = isBishop ? calculateBishopOccupancyMask(1ULL << sq)
                  : calculateRookOccupancyMask(1ULL << sq); // Get blocker mask
  n = count1s(mask);                                        // Number of relevant bits
  isBishop ? assert(n <= 9) : assert(n <= 12);              // optional safety check

  // Generate all 2^n (1 << n) blocker combinations and attack results
  for (i = 0; i < (1 << n); i++) {
    blockersArr[i] = permIndexToBlockerMask(i, n, mask);
    attackArr[i] = isBishop ? bishopAttacksFromBlocker(sq, blockersArr[i], showLog)
                            : rookAttacksFromBlocker(sq, blockersArr[i], showLog);
  }

  // Try up to 100 million random candidates
  for (genNumber = 0; genNumber < 100000000; genNumber++) {
    magic = random_uint64_t_fewbits();
    if (showLog && (genNumber % 10000 == 0))
      SDL_Log("%s: sq #%d, Attemp#%d: trying %lx", piece.c_str(), sq, genNumber, magic);

    // Optional heuristic: reject bad magic candidates early
    if (count1s((mask * magic) & 0xFF00000000000000ULL) < 6) {
      continue;
    }

    /*if (showLog && (genNumber % 100000 == 0))*/
    /*  SDL_Log("Possible good magic number.");*/

    for (i = 0, fail = 0; !fail && i < (1 << n); i++) {
      j = transformToIndex(blockersArr[i], magic, numBits);

      if (generation[j] != genNumber) {
        // used[j] has not been used in this generation
        generation[j] = genNumber; // Mark it as used for this generation
        used[j] = attackArr[i];    // Store the attack for this blocker configuration
      } else if (used[j] != attackArr[i]) {
        // used[j] was already used in this generation,
        // and the attack doesn't match: collision detected
        fail = true;
        break;
      }
    }

    if (!fail)
      return magic; // Success!
  }
  printf("***Failed***\n");
  return 0ULL;
}

} // namespace Bitboards
