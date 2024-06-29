#include "game/chess.h"
#include "game/inits.h"
#include "utils.h"

void Chess::initGame() {
  bitboards = {pawnInit,
               horseInit,
               castleInit,
               bishopInit,
               queenInit,
               kingInit,
               reverseU64(pawnInit),
               reverseU64(horseInit),
               reverseU64(castleInit),
               reverseU64(bishopInit),
               reverseU64(queenInit),
               reverseU64(kingInit)};
};
