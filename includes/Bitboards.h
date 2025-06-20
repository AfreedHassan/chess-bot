#ifndef BITBOARDS_H
#define BITBOARDS_H

#include <cstdint>

namespace Bitboards {

void showBitboard(uint64_t bb);

inline constexpr uint64_t initialBlackPawns = 0x00ff000000000000ULL;
inline constexpr uint64_t initialWhitePawns = 0x000000000000ff00ULL;

inline constexpr uint64_t initialWhiteBishops = 0x0000000000000024;
inline constexpr uint64_t initialBlackBishops = 0x2400000000000000;

inline constexpr uint64_t initialWhiteKnights = 0x0000000000000042;
inline constexpr uint64_t initialBlackKnights = 0x4200000000000000;

inline constexpr uint64_t initialWhiteRooks = 0x0000000000000081;
inline constexpr uint64_t initialBlackRooks = 0x8100000000000000;

inline constexpr uint64_t initialWhiteQueens = 0x0000000000000008;
inline constexpr uint64_t initialBlackQueens = 0x0800000000000000;

inline constexpr uint64_t initialWhiteKing = 0x0000000000000010;
inline constexpr uint64_t initialBlackKing = 0x1000000000000000;

inline constexpr uint64_t notAFile = 0xfefefefefefefefe;  // ~0x0101010101010101
inline constexpr uint64_t notABFile = 0xfcfcfcfcfcfcfcfc; // ~0x0101010101010101

inline constexpr uint64_t notGHFile = 0x3f3f3f3f3f3f3f3f;     // ~0x8080808080808080
inline constexpr uint64_t notHFile = 0x7f7f7f7f7f7f7f7f;      // ~0x8080808080808080
                                                              //
inline constexpr uint64_t NotFirstRank = 0x00ffffffffffffff;  // ~0x8080808080808080
inline constexpr uint64_t NotEighthRank = 0x00ffffffffffffff; // ~0x8080808080808080

uint64_t shiftSouth(uint64_t b);
uint64_t shiftNorth(uint64_t b);
uint64_t shiftEast(uint64_t b);
uint64_t shiftWest(uint64_t b);

uint64_t shiftNortheast(uint64_t b);
uint64_t shiftSoutheast(uint64_t b);
uint64_t shiftSouthwest(uint64_t b);
uint64_t shiftNorthwest(uint64_t b);

uint64_t fillSouth(uint64_t gen);
uint64_t fillNorth(uint64_t gen);
uint64_t fillEast(uint64_t gen);

uint64_t fillWest(uint64_t gen);
uint64_t fillFile(uint64_t gen);
uint64_t fillRank(uint64_t gen);

uint64_t fillNoEa(uint64_t gen);
uint64_t fillSoEe(uint64_t gen);
uint64_t fillSoWe(uint64_t gen);
uint64_t fillNoWe(uint64_t gen);

uint64_t fillDiag(uint64_t gen);
uint64_t fillAntiDiag(uint64_t gen);

uint64_t knightFill(uint64_t knights);

uint64_t wSinglePushTargets(uint64_t wpawns, uint64_t empty);
uint64_t wDblPushTargets(uint64_t wpawns, uint64_t empty);

uint64_t bSinglePushTargets(uint64_t bpawns, uint64_t empty);
uint64_t bDoublePushTargets(uint64_t bpawns, uint64_t empty);

uint64_t wPawnsAbleToPush(uint64_t wpawns, uint64_t empty);
uint64_t wPawnsAbleToDoublePush(uint64_t wpawns, uint64_t empty);

uint64_t bPawnsAbleToPush(uint64_t wpawns, uint64_t empty);
uint64_t bPawnsAbleToDoublePush(uint64_t wpawns, uint64_t empty);

inline uint64_t arrKnightAttacks[64];
inline uint64_t arrKingAttacks[64];

// knight stuff
/*knight pattern
   *
   *     noNoWe    noNoEa
            +15  +17
             |     |
noWeWe  +6 __|     |__+10  noEaEa
              \   /
               >0<
           __ /   \ __
soWeWe -10   |     |   -6  soEaEa
             |     |
            -17  -15
        soSoWe    soSoEa
   *
   */
void initKnightAttacks();
uint64_t getKnightAttacks(uint64_t bb);
uint64_t knightFill(uint64_t knights);
uint64_t forkTargetSquare(uint64_t targets);

// king stuff
uint64_t getKingAttacks(uint64_t kingSet);
void initKingAttacks();

// sliding pieces (rook, bishop) stuff.
inline constexpr uint8_t RookNumBitsOccupancyMask[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12};

inline constexpr uint8_t BishopNumBitsOccupancyMask[64] = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6};

void getRookOccMask(uint64_t bb);
void getBishopOccMask(uint64_t bb);
} // namespace Bitboards

#endif // BITBOARDS_H
