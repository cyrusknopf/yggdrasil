#include <gtest/gtest.h>

#include "game/chess.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"

TEST(rollout, whiteWin) {
    team white = {1, 0, 0, 0, 0, 3};
    team black = {8, 0, 0, 0, 0, 0};

    GameNode root = initialiseTree(white, black);

    int res = simulate(&root);

    ASSERT_EQ(1, res);
}

TEST(rollout, blackWin) {
    team black = {1, 0, 0, 0, 0, 3};
    team white = {8, 0, 0, 0, 0, 0};

    GameNode root = initialiseTree(white, black);

    int res = simulate(&root);

    ASSERT_EQ(-1, res);
}

/*
TEST(rollout, a) {
    std::pair<team, team> starts = initGame();

    GameNode root = initialiseTree(starts.first, starts.second);

    simulate(&root);
}
*/
