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

TEST(simulate, whiteWin) {
    team white = {1, 0, 0, 0, 0, 3};
    team black = {8, 0, 0, 0, 0, 0};

    GameNode* root = initialiseTree(white, black);

    std::optional<bool> res = simulate(root, true);

    ASSERT_EQ(true, res);
}

TEST(simulate, blackWin) {
    team black = {1, 0, 0, 0, 0, 3};
    team white = {8, 0, 0, 0, 0, 0};

    GameNode* root = initialiseTree(white, black);

    std::optional<bool> res = simulate(root, true);

    ASSERT_EQ(false, res);
}
