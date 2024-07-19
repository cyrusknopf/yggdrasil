#include <gtest/gtest.h>

#include <cstdlib>
#include <vector>

#include "mcts/gametree.h"

TEST(getChildren, onlyChild) {
    team t;
    GameNode parent = GameNode(nullptr, 0, t, t, true);

    GameNode child = GameNode(&parent, 1, t, t, false);
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

    GameNode child = GameNode(&parent, 0, t, t, false);
    parent.addChild(&child);

    GameNode* randomKid = parent.getRandomChild(seed);

    // addr of child == returned pointer
    ASSERT_EQ(&child, randomKid);
}

TEST(getRandomChild, threeChildren) {
    // When this seed is used it returns the second child
    int seed = 1;
    team t;

    GameNode parent = GameNode(nullptr, 0, t, t, true);

    GameNode child1 = GameNode(&parent, 0, t, t, false);
    parent.addChild(&child1);

    GameNode child2 = GameNode(&parent, 0, t, t, false);
    parent.addChild(&child2);

    GameNode child3 = GameNode(&parent, 0, t, t, false);
    parent.addChild(&child3);

    GameNode* randomKid = parent.getRandomChild(seed);

    // addr of child2 == returned pointer
    ASSERT_EQ(&child2, randomKid);
}

TEST(evaluate, oneToOne) { FAIL(); }
