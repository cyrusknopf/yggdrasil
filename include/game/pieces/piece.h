#include "utils.h"
#include <vector>

class Piece {
public:
  bool colour;
  virtual std::vector<bitboard> getPseudoLegalMoves(bool colour) = 0;
};
