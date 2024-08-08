#include <game/moves.h>
#include <gtest/gtest.h>

#include "game/chess.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "utils.h"

TEST(makeMove, capture) {
    // White to move
    bool turn = true;
    // White king at a2
    team white = {0, 0, 0, 0, 0, 0x8000};
    // Black king at a3
    team black = {0, 0, 0, 0, 0, 0x800000};
    // Move to a3
    bitboard captureMove = 0x800000;
    // King is moving
    int idx = 5;

    std::pair<team, team> newBoards =
        makeMove(white, black, captureMove, idx, turn);

    // Black king should've been captured
    ASSERT_EQ(0, newBoards.second.at(5));
    // White king should be in new location
    ASSERT_EQ(captureMove, newBoards.first.at(5));
}

TEST(getAllLegalMoves, pawn) {
    bitboard whitePawn = coordinateToState("a2");
    team white = {whitePawn, 0, 0, 0, 0, 0};
    team black = {0, 0, 0, 0, 0, 0};
    std::vector<std::pair<bitboard, int>> moves =
        getAllLegalMoves(white, black, true);
    ASSERT_EQ(2, moves.size());
    ASSERT_EQ(0, moves.at(0).second);
    ASSERT_EQ(0, moves.at(1).second);
}

TEST(simulate, blackMated) {
    bitboard whiteKing = 0x0000000000000040;
    bitboard whiteCastle = 0x0080000000000000;

    bitboard blackKing = 0x0000000000000080;

    team white = {0, 0, whiteCastle, 0, 0, whiteKing};
    team black = {0, 0, 0, 0, 0, blackKing};

    GameNode node = GameNode(nullptr, 0, white, black, false);

    std::optional<bool> res = simulate(&node, true);

    ASSERT_FALSE(res);
}

TEST(simulate, whiteMated) {
    bitboard blackKing = coordinateToState("g1");
    bitboard blackHorse = coordinateToState("e7");
    bitboard blackCastle = coordinateToState("e3");

    bitboard whitePawn = coordinateToState("g7");
    bitboard whiteKing = coordinateToState("h7");

    team white = {whitePawn, 0, 0, 0, 0, whiteKing};
    team black = {0, blackHorse, blackCastle, 0, 0, blackKing};

    GameNode node = GameNode(nullptr, 0, white, black, false);

    std::optional<bool> res = simulate(&node, true);

    ASSERT_FALSE(res);
}

TEST(simulate, terminal) {
    team white = {0, 0, 9223372036854775808ULL, 0, 0, 35184372088832};
    team black = {0, 0, 0, 0, 0, 2305843009213693952};

    GameNode* node = new GameNode(nullptr, 0, white, black, false);
    ASSERT_FALSE(node->getTerminal());
    std::optional<bool> res = simulate(node, true);
    ASSERT_TRUE(res);
}
