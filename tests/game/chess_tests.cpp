#include <gtest/gtest.h>

#include "game/chess.h"

TEST(isMated, whiteMated) {
    bitboard whiteKing = coordinateToState("a1");
    bitboard blackCastles = coordinateToState("a3") | coordinateToState("c1");
    bitboard blackBishop = coordinateToState("c3");
    team white = {0, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, blackCastles, blackBishop, 0, 0};

    bool mated = isMated(white, black, true);

    ASSERT_EQ(true, mated);
}
