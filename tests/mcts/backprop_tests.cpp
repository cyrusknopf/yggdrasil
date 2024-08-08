#include <gtest/gtest.h>

#include "mcts/backprop.h"
#include "mcts/gametree.h"

TEST(backprop, oneGeneration) {
    team t;
    GameNode* root = initialiseTree(t, t);
    GameNode* child = root->addChild(root, 10, t, t);

    ASSERT_EQ(root->getWins(), 0);   // Start state, white to move
    ASSERT_EQ(child->getWins(), 0);  // White move, black to move

    // We assume that at this stage the game is over, since black is to move
    // then white won
    backpropagate(child, true);  // Win at state where black to move

    // Root is opponent to leaf so should be 0
    ASSERT_EQ(root->getWins(), 1);
    ASSERT_EQ(child->getWins(), 0);
}

TEST(backprop, threeGenerations) {
    team t;
    // Start state, white to move
    GameNode* root = initialiseTree(t, t);
    // White move, black to move
    GameNode* child = root->addChild(root, 10, t, t);
    // Black move, white to move
    GameNode* gchild = child->addChild(child, 11, t, t);
    // We say gchild is terminal, since white is to move then black won

    ASSERT_EQ(root->getWins(), 0);
    ASSERT_EQ(child->getWins(), 0);
    ASSERT_EQ(gchild->getWins(), 0);

    backpropagate(gchild, false);

    // Leaf values are actually updated in `simulate` so should still be 0
    // Root is opponent to leaf so should also be 0
    ASSERT_EQ(root->getWins(), 0);
    ASSERT_EQ(child->getWins(), 1);
    ASSERT_EQ(gchild->getWins(), 0);
}
