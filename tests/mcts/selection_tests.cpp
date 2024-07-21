#include <gtest/gtest.h>

#include "mcts/selection.h"

TEST(selectRandomLeaf, orphan) {
    int seed = 1;
    team t;

    GameNode root = GameNode(nullptr, 0, t, t, false);

    GameNode* leaf = selectRandomLeaf(&root, seed);

    ASSERT_EQ(&root, leaf);
}

TEST(selectRandomLeaf, onlyChild) {
    int seed = 1;
    team t;

    GameNode parent = GameNode(nullptr, 0, t, t, false);

    GameNode child = GameNode(&parent, 0, t, t, false);
    parent.addChild(&child);

    GameNode* leaf = selectRandomLeaf(&parent, seed);

    ASSERT_EQ(&child, leaf);
}

TEST(selectRandomLeaf, grandParent) {
    int seed = 1;
    team t;

    GameNode parent = GameNode(nullptr, 0, t, t, false);

    GameNode child = GameNode(&parent, 0, t, t, false);
    parent.addChild(&child);

    GameNode grandChild = GameNode(&child, 0, t, t, false);
    child.addChild(&grandChild);

    GameNode* leaf = selectRandomLeaf(&parent, seed);

    ASSERT_EQ(&grandChild, leaf);
}

TEST(heuristicSelectLeaf, oneGenerationWhite) {
    team t;
    GameNode parent = GameNode(nullptr, 0, t, t, true);

    GameNode child1 = GameNode(&parent, 0, t, t, false);
    child1.alterScore(-100);
    parent.addChild(&child1);

    GameNode child2 = GameNode(&parent, 0, t, t, false);
    child2.alterScore(-99);
    parent.addChild(&child2);

    GameNode child3 = GameNode(&parent, 0, t, t, false);
    child3.alterScore(50);
    parent.addChild(&child3);

    GameNode child4 = GameNode(&parent, 0, t, t, false);
    child4.alterScore(100);
    parent.addChild(&child4);

    GameNode* bestChild = heursiticSelectLeaf(&parent);

    ASSERT_EQ(bestChild, &child4);
}

TEST(heuristicSelectLeaf, oneGenerationBlack) {
    team t;
    GameNode parent = GameNode(nullptr, 0, t, t, false);

    GameNode child1 = GameNode(&parent, 0, t, t, false);
    child1.alterScore(-100);
    parent.addChild(&child1);

    GameNode child2 = GameNode(&parent, 0, t, t, false);
    child2.alterScore(-99);
    parent.addChild(&child2);

    GameNode child3 = GameNode(&parent, 0, t, t, false);
    child3.alterScore(50);
    parent.addChild(&child3);

    GameNode child4 = GameNode(&parent, 0, t, t, false);
    child4.alterScore(100);
    parent.addChild(&child4);

    GameNode* bestChild = heursiticSelectLeaf(&parent);

    ASSERT_EQ(bestChild, &child1);
}
