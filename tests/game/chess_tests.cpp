#include <gtest/gtest.h>

#include "game/chess.h"
#include "utils.h"

TEST(getWinner, whiteMated) {
    bitboard whiteKing = coordinateToState("a1");
    bitboard blackCastles = coordinateToState("a3") | coordinateToState("c1");
    bitboard blackBishop = coordinateToState("c3");
    team white = {0, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, blackCastles, blackBishop, 0, 0};

    std::optional<bool> winner = getWinner(white, black);
    ASSERT_EQ(false, winner);
}
