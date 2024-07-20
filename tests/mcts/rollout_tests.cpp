#include <gtest/gtest.h>

#include "game/chess.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"

TEST(rollout, a) {
    std::pair<team, team> starts = initGame();

    GameNode root = initialiseTree(starts.first, starts.second);

    simulate(&root);
}
