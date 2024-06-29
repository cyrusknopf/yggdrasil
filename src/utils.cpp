#include <cstdint>
#include <immintrin.h>

uint64_t reverseU64(uint64_t X) { return __bswap_64(X); }
