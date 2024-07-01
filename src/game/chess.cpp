#include "game/chess.h"
#include "game/inits.h"
#include "utils.h"
#include <cstdint>

void Chess::initGame() {
  /* utils.h contains the 64 bit start state of each white piece.
   * Reversing these gives the black piece start states.
   */
  whiteBitboards = {pawnInit,   horseInit, castleInit,
                    bishopInit, queenInit, kingInit};

  // TODO Change these to contants
  blackBitboards = {reverseU64(pawnInit),   reverseU64(horseInit),
                    reverseU64(castleInit), reverseU64(bishopInit),
                    reverseU64(queenInit),  reverseU64(kingInit)};
};

uint64_t Chess::getGameState() {
  return getGameState(true) | getGameState(false);
}

uint64_t Chess::getGameState(bool colour) {
  uint64_t state = 0;
  if (colour) {
    for (auto &board : whiteBitboards) {
      state |= board;
    }
  } else {
    for (auto &board : blackBitboards) {
      state |= board;
    }
  }
  return state;
}
