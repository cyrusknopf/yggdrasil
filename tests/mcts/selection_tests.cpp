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
