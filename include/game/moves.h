#include <cstdint>
#include <vector>

class Pawn {
public:
  std::vector<uint64_t> makeMoves(uint64_t state, bool colour);
};

class King {
public:
  std::vector<uint64_t> getPseudoLegalMoves(uint64_t state, bool colour);
};
