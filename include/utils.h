#include <cstdint>

using bitboard = uint64_t;

bitboard reverseU64(bitboard X);

int getRank(bitboard state);

int getFile(bitboard state);

bitboard slideNorth(bitboard state);
bitboard slideNorthEast(bitboard state);
bitboard slideEast(bitboard state);
bitboard slideSouthEast(bitboard state);
bitboard slideSouth(bitboard state);
bitboard slideSouthWest(bitboard state);
bitboard slideWest(bitboard state);
bitboard slideNorthWest(bitboard state);
