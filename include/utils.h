#include <cstdint>

uint64_t reverseU64(uint64_t X);

int getRank(uint64_t state);

int getFile(uint64_t state);

uint64_t slideNorth(uint64_t state);
uint64_t slideNorthEast(uint64_t state);
uint64_t slideEast(uint64_t state);
uint64_t slideSouthEast(uint64_t state);
uint64_t slideSouth(uint64_t state);
uint64_t slideSouthWest(uint64_t state);
uint64_t slideWest(uint64_t state);
uint64_t slideNorthWest(uint64_t state);
