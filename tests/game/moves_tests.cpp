#include "game/moves.h"
#include <gtest/gtest.h>
#include <iostream>
#include <ostream>

TEST(horsePseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = horsePseudoLegalMoves(0, 0, state, true);

    ASSERT_EQ(8, moves.size());

    bitboard allCorrectMoves = 0x0000142200221400;

    bitboard allMoves = 0;
    for (auto &move : moves) {
        std::cout << move << std::endl;
        allMoves |= move;
    }

    ASSERT_EQ(allCorrectMoves, allMoves);
}
