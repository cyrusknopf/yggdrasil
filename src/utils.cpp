#include "utils.h"
#include <cstdint>
#include <immintrin.h>

uint64_t reverseU64(uint64_t X) { return __bswap_64(X); }

int getFile(uint64_t state) {
  /*
   * Since file is independent of rank, we shift the piece into rank 1 for
   * simplicity
   */
  uint64_t tempState = state;
  while (tempState > 128) {
    tempState >>= 8;
  }

  /*
   * Find the log2 of the state. Since the state is guaranteed to be a binary
   * number with a single 1, this is correct.
   */
  int exp = 0;
  while ((tempState & 0b1) == 0) {
    tempState >>= 1;
    exp++;
  }

  return 8 - exp;
}

int getRank(uint64_t state) {
  int rank = 0;
  uint64_t tempState = state;
  while (tempState != 0) {
    tempState >>= 8;
    rank++;
  }
  return rank;
}
