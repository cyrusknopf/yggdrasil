#include <gtest/gtest.h>

#include "mcts/gametree.h"
#include "mcts/selection.h"

TEST(selectRandomLeaf, orphan) {
    int seed = 1;
    team t = {0, 0, 0, 0, 0, 0};

    GameNode* root = initialiseTree(t, t);

    GameNode* leaf = selectRandomLeaf(root, seed);

    ASSERT_EQ(root, leaf);
}

TEST(selectRandomLeaf, onlyChild) {
    int seed = 1;
    team t = {0, 0, 0, 0, 0, 0};

    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(parent, 0, t, t);

    GameNode* leaf = selectRandomLeaf(parent, seed);

    ASSERT_EQ(child, leaf);
}

TEST(selectRandomLeaf, grandParent) {
    int seed = 1;
    team t;

    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(parent, 0, t, t);

    GameNode* grandChild = child->addChild(child, 0, t, t);

    GameNode* leaf = selectRandomLeaf(parent, seed);

    ASSERT_EQ(grandChild, leaf);
}

TEST(heuristicSelectLeaf, oneGenerationWhite) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child1 = parent->addChild(parent, 0, t, t);
    child1->alterScore(-100);

    GameNode* child2 = parent->addChild(parent, 0, t, t);
    child2->alterScore(-99);

    GameNode* child3 = parent->addChild(parent, 0, t, t);
    child3->alterScore(50);

    GameNode* child4 = parent->addChild(parent, 0, t, t);
    child4->alterScore(100);

    GameNode* bestChild = heursiticSelectLeaf(parent);

    // Should be the child with the highest value
    ASSERT_EQ(bestChild, child4);
}

TEST(heuristicSelectLeaf, oneGenerationBlack) {
    team t;
    // Use new here instead of initialiseTree since we need to force black turn
    GameNode* parent = new GameNode(nullptr, 0, t, t, false);

    GameNode* child1 = parent->addChild(parent, 0, t, t);
    child1->alterScore(-100);

    GameNode* child2 = parent->addChild(parent, 0, t, t);
    child2->alterScore(-99);

    GameNode* child3 = parent->addChild(parent, 0, t, t);
    child3->alterScore(50);

    GameNode* child4 = parent->addChild(parent, 0, t, t);
    child4->alterScore(100);

    GameNode* bestChild = heursiticSelectLeaf(parent);

    // Should be the child with the lowest value
    ASSERT_EQ(bestChild, child1);
}
