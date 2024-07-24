#include <gtest/gtest.h>

#include "mcts/backprop.h"
#include "mcts/gametree.h"

TEST(backprop, oneGeneration) {
    team t;
    GameNode* root = initialiseTree(t, t);
    GameNode* child = root->addChild(root, 10, t, t);

    ASSERT_EQ(root->getWins(), 0);
    ASSERT_EQ(child->getWins(), 0);

    backpropagate(child, false);

    // Leaf values are actually updated in `simulate` so should still be 0
    // Root is opponent to leaf so should also be 0
    ASSERT_EQ(root->getWins(), 0);
    ASSERT_EQ(child->getWins(), 0);
}

TEST(backprop, threeGenerations) {
    team t;
    GameNode* root = initialiseTree(t, t);
    GameNode* child = root->addChild(root, 10, t, t);

    GameNode* gchild = child->addChild(child, 11, t, t);
    ASSERT_EQ(root->getWins(), 0);
    ASSERT_EQ(child->getWins(), 0);
    ASSERT_EQ(gchild->getWins(), 0);

    backpropagate(gchild, 1);

    // Leaf values are actually updated in `simulate` so should still be 0
    // Root is opponent to leaf so should also be 0
    ASSERT_EQ(root->getWins(), 1);
    ASSERT_EQ(child->getWins(), 0);
    ASSERT_EQ(gchild->getWins(), 0);
}
