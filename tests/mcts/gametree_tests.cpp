#include <gtest/gtest.h>

#include <cstdlib>
#include <vector>

#include "mcts/gametree.h"

TEST(getChildren, onlyChild) {
    team t;
    GameNode parent = GameNode(nullptr, 0, t, t, true);
    GameNode child = GameNode(nullptr, 1, t, t, false);

    parent.addChild(&child);

    std::vector<GameNode*> kids = parent.getChildren();

    ASSERT_EQ(1, kids.size());

    GameNode* kid = kids[0];

    // addr of child == returned pointer
    ASSERT_EQ(&child, kid);
}

TEST(getRandomChild, onlyChild) {
    int seed = 1;
    team t;
    GameNode parent = GameNode(nullptr, 0, t, t, true);
    GameNode child = GameNode(nullptr, 0, t, t, false);

    parent.addChild(&child);

    GameNode* randomKid = parent.getRandomChild(seed);

    // addr of child == returned pointer
    ASSERT_EQ(&child, randomKid);
}

TEST(getRandomChild, threeChildren) {
    // When this seed is used it returns the second child
    int seed = 1;

    team t;
    GameNode x = GameNode(nullptr, 0, t, t, true);
    GameNode child1 = GameNode(nullptr, 0, t, t, false);
    GameNode child2 = GameNode(nullptr, 0, t, t, false);
    GameNode child3 = GameNode(nullptr, 0, t, t, false);

    x.addChild(&child1);
    x.addChild(&child2);
    x.addChild(&child3);

    GameNode* randomKid = x.getRandomChild(seed);

    // addr of child2 == returned pointer
    ASSERT_EQ(&child2, randomKid);
}
