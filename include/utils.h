#ifndef _UTILSH_
#define _UTILSH_

#include <cstdint>
#include <regex>
#include <vector>

using bitboard = uint64_t;

bitboard reverseU64(bitboard X);

int getRank(bitboard state);

int getFile(bitboard state);

bitboard slideNorth(bitboard state);
bitboard slideEast(bitboard state);
bitboard slideSouth(bitboard state);
bitboard slideWest(bitboard state);

std::vector<bitboard> getAllPieces(bitboard state);

const std::regex squareRe{"[a-h][1-8]"};

void clearTerm();

// bitboard slideSouthEast(bitboard state);
// bitboard slideSouthWest(bitboard state);
// bitboard slideNorthWest(bitboard state);
// bitboard slideNorthEast(bitboard state);

#endif // !_UTILSH_
