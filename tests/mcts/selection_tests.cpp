#include <gtest/gtest.h>

#include "mcts/selection.h"

TEST(selectRandomLeaf, orphan) {
    int seed = 1;
    GameNode x = GameNode(nullptr, 0, nullptr, nullptr, 1., false);

    GameNode leaf = selectRandomLeaf(x, seed);

    ASSERT_EQ(1., leaf.getValue());
}

TEST(selectRandomLeaf, onlyChild) {
    int seed = 1;
    GameNode x = GameNode(nullptr, 0, nullptr, nullptr, 1., false);
    GameNode child = GameNode(nullptr, 0, nullptr, nullptr, 2., false);

    x.addChild(&child);

    GameNode leaf = selectRandomLeaf(x, seed);

    ASSERT_EQ(2., leaf.getValue());
}

TEST(selectRandomLeaf, grandParent) {
    int seed = 1;
    GameNode x = GameNode(nullptr, 0, nullptr, nullptr, 1., false);
    GameNode child = GameNode(nullptr, 0, nullptr, nullptr, 2., false);
    GameNode grandChild = GameNode(nullptr, 0, nullptr, nullptr, 3., false);

    child.addChild(&grandChild);
    x.addChild(&child);

    GameNode leaf = selectRandomLeaf(x, seed);

    ASSERT_EQ(3., leaf.getValue());
}
