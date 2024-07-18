#include <gtest/gtest.h>

#include <vector>

#include "mcts/gametree.h"

TEST(getChildren, onlyChild) {
    GameNode x = GameNode(nullptr, 0, nullptr, nullptr, 1., true);
    GameNode child = GameNode(nullptr, 0, nullptr, nullptr, 1., false);

    x.addChild(&child);

    std::vector<GameNode*> kids = x.getChildren();

    ASSERT_EQ(1, kids.size());

    GameNode kid = *kids[0];

    ASSERT_EQ(1., kid.getValue());
}

TEST(getRandomChild, onlyChild) {
    GameNode x = GameNode(nullptr, 0, nullptr, nullptr, 0., true);
    GameNode child = GameNode(nullptr, 0, nullptr, nullptr, 1., false);

    x.addChild(&child);

    GameNode randomKid = x.getRandomChild(1);

    ASSERT_EQ(1., randomKid.getValue());
}

TEST(getRandomChild, threeChildren) {
    // When this seed is used it returns the second child
    int seed = 1;

    GameNode x = GameNode(nullptr, 0, nullptr, nullptr, 0., true);
    GameNode child1 = GameNode(nullptr, 0, nullptr, nullptr, 0., false);
    GameNode child2 = GameNode(nullptr, 0, nullptr, nullptr, 1., false);
    GameNode child3 = GameNode(nullptr, 0, nullptr, nullptr, 2., false);

    x.addChild(&child1);
    x.addChild(&child2);
    x.addChild(&child3);

    GameNode randomKid = x.getRandomChild(seed);

    ASSERT_EQ(1., randomKid.getValue());
}
