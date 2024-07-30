#include <gtest/gtest.h>

#include "game/chess.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "utils.h"

TEST(makeSimulatedMove, capture) {
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
        makeSimulatedMove(white, black, captureMove, idx, turn);

    // Black king should've been captured
    ASSERT_EQ(0, newBoards.second.at(5));
    // White king should be in new location
    ASSERT_EQ(captureMove, newBoards.first.at(5));
}

TEST(simulate, blackWin) {
    bitboard whiteKing = coordinateToState("a1");
    bitboard blackCastles = coordinateToState("a3") | coordinateToState("c1");
    bitboard blackBishop = coordinateToState("c3");
    team white = {0, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, blackCastles, blackBishop, 0, 0};

    GameNode* root = initialiseTree(white, black);

    std::optional<bool> res = simulate(root, true);

    ASSERT_EQ(false, res);
}

TEST(simulate, whiteWin) {
    bitboard blackKing = coordinateToState("a1");
    bitboard whiteCastles = coordinateToState("a3") | coordinateToState("c1");
    bitboard whiteBishop = coordinateToState("c3");
    team black = {0, 0, 0, 0, 0, blackKing};
    team white = {0, 0, whiteCastles, whiteBishop, 0, 0};

    GameNode* root = initialiseTree(white, black);
    root->nextTurn();

    std::optional<bool> res = simulate(root, true);

    ASSERT_EQ(true, res);
}
