#include "utils.h"
#include <cstdint>
#include <vector>

class Pawn {
public:
  std::vector<uint64_t> makeMoves(uint64_t state, bool colour) {
    std::vector<uint64_t> moves;
    uint64_t move;

    if (colour) {
      if (getRank(state) == 2) {
        move = state << 8;
      }
    }

    return moves;
  }
};

class King {
public:
  std::vector<uint64_t> getPseudoLegalMoves() {
    std::vector<uint64_t> moves;
    return moves;
  }
};
