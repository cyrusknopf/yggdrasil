#include <gtest/gtest.h>

#include "mcts/backprop.h"
#include "mcts/gametree.h"

TEST(backprop, oneGeneration) {
    team t;
    GameNode* root = initialiseTree(t, t);
    GameNode* child = root->addChild(root, 10, t, t);

    ASSERT_EQ(root->getScore(), 0);
    ASSERT_EQ(child->getScore(), 0);

    backpropagate(child, 1);

    // Leaf values are actually updated in `simulate` so should still be 0
    ASSERT_EQ(root->getScore(), 1);
    ASSERT_EQ(child->getScore(), 0);
}

TEST(backprop, twoGenerations) {
    team t;
    GameNode* root = initialiseTree(t, t);
    GameNode* child = root->addChild(root, 10, t, t);

    ASSERT_EQ(root->getScore(), 0);
    ASSERT_EQ(child->getScore(), 0);

    backpropagate(child, 1);

    // Leaf values are actually updated in `simulate` so should still be 0
    ASSERT_EQ(root->getScore(), 1);
    ASSERT_EQ(child->getScore(), 0);
}

TEST(backprop, threeGenerations) {
    team t;
    GameNode* root = initialiseTree(t, t);
    GameNode* child = root->addChild(root, 10, t, t);
    GameNode* gchild = child->addChild(child, 11, t, t);

    ASSERT_EQ(root->getScore(), 0);
    ASSERT_EQ(child->getScore(), 0);
    ASSERT_EQ(gchild->getScore(), 0);

    backpropagate(gchild, 1);

    // Leaf values are actually updated in `simulate` so should still be 0
    ASSERT_EQ(root->getScore(), 1);
    ASSERT_EQ(child->getScore(), 1);
    ASSERT_EQ(gchild->getScore(), 0);
}
