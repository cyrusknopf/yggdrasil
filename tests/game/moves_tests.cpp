#include "game/moves.h"
#include <gtest/gtest.h>

TEST(pawnPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = pawnPseudoLegalMoves(0, 0, state, true);

    ASSERT_EQ(1, moves.size());

    bitboard allCorrectMoves = 0x0000000800000000;

    bitboard allMoves = 0;
    for (auto &move : moves) {
        allMoves |= move;
    }

    ASSERT_EQ(allCorrectMoves, allMoves);
}

TEST(horsePseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = horsePseudoLegalMoves(0, 0, state);

    ASSERT_EQ(8, moves.size());

    bitboard allCorrectMoves = 0x0000142200221400;

    bitboard allMoves = 0;
    for (auto &move : moves) {
        allMoves |= move;
    }

    ASSERT_EQ(allCorrectMoves, allMoves);
}

TEST(castlePseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = castlePseudoLegalMoves(0, 0, state);

    ASSERT_EQ(14, moves.size());

    bitboard allCorrectMoves = 0x08080808F7080808;

    bitboard allMoves = 0;
    for (auto &move : moves) {
        allMoves |= move;
    }

    ASSERT_EQ(allCorrectMoves, allMoves);
}

TEST(bishopPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = bishopPseudoLegalMoves(0, 0, state);

    ASSERT_EQ(13, moves.size());

    // The board state which contains every legal move should be:
    // 1 0 0 0 0 0 0 0 | 8 0
    // 0 1 0 0 0 0 0 1 | 4 1
    // 0 0 1 0 0 0 1 0 | 2 2
    // 0 0 0 1 0 1 0 0 | 1 4
    // 0 0 0 0 0 0 0 0 | 0 0
    // 0 0 0 1 0 1 0 0 | 1 4
    // 0 0 1 0 0 0 1 0 | 2 2
    // 0 1 0 0 0 0 0 1 | 4 1

    bitboard allCorrectMoves = 0x8041221400142241;

    bitboard allMoves = 0;
    for (auto &move : moves) {
        allMoves |= move;
    }

    ASSERT_EQ(allCorrectMoves, allMoves);
}

TEST(queenPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = queenPseudoLegalMoves(0, 0, state);

    ASSERT_EQ(27, moves.size());

    long allCorrectMoves = 0x88492A1CF71C2A49L;

    bitboard allMoves = 0;
    for (auto &move : moves) {
        allMoves |= move;
    }

    ASSERT_EQ(allCorrectMoves, allMoves);
}

TEST(kingPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = kingPseudoLegalMoves(0, 0, state);

    ASSERT_EQ(8, moves.size());

    bitboard allCorrectMoves = 0x0000001C141C0000;

    bitboard allMoves = 0;
    for (auto &move : moves) {
        allMoves |= move;
    }

    ASSERT_EQ(allCorrectMoves, allMoves);
}
