#ifndef _UTILSH_
#define _UTILSH_

#include <array>
#include <cstdint>
#include <regex>
#include <vector>

using bitboard = uint64_t;
using team = std::array<bitboard, 6>;
const std::regex squareRe{"[a-h][1-8]"};

int getRank(bitboard state);

int getFile(bitboard state);

bitboard coordinateToState(const std::string &coord);

bitboard slideNorth(bitboard state);
bitboard slideEast(bitboard state);
bitboard slideSouth(bitboard state);
bitboard slideWest(bitboard state);

std::vector<bitboard> getAllPieces(bitboard state);

std::pair<bitboard, int> findPiece(bitboard square,
                                   std::array<bitboard, 6> &target);

bitboard performCapture(bitboard victim, bitboard captor);

void clearTerm();
#endif // !_UTILSH_
