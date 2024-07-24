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

TEST(heuristicSelectLeaf, oneGeneration) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child1 = parent->addChild(parent, 0, t, t);
    child1->incrWins();

    GameNode* child2 = parent->addChild(parent, 0, t, t);
    child2->incrWins();
    child2->incrWins();

    GameNode* child3 = parent->addChild(parent, 0, t, t);
    child3->incrWins();
    child3->incrWins();
    child3->incrWins();

    GameNode* child4 = parent->addChild(parent, 0, t, t);
    child4->incrWins();
    child4->incrWins();
    child4->incrWins();
    child4->incrWins();

    GameNode* bestChild = heursiticSelectLeaf(parent);

    // Should be the child with the highest value
    ASSERT_EQ(bestChild, child4);
}
