#include <gtest/gtest.h>

#include <cstdlib>
#include <vector>

#include "mcts/gametree.h"

TEST(getChildren, onlyChild) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(parent, 1, t, t);

    std::vector<GameNode*> kids = parent->getChildren();

    ASSERT_EQ(1, kids.size());

    GameNode* kid = kids[0];

    // addr of child == returned pointer
    ASSERT_EQ(child, kid);
}

TEST(getRandomChild, onlyChild) {
    int seed = 1;
    team t;

    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(parent, 0, t, t);

    GameNode* randomKid = parent->getRandomChild(seed);

    // addr of child == returned pointer
    ASSERT_EQ(child, randomKid);
}

TEST(getRandomChild, threeChildren) {
    // When this seed is used it returns the second child
    int seed = 1;
    team t;

    GameNode* parent = initialiseTree(t, t);

    GameNode* child1 = parent->addChild(parent, 0, t, t);

    GameNode* child2 = parent->addChild(parent, 0, t, t);

    GameNode* child3 = parent->addChild(parent, 0, t, t);

    GameNode* randomKid = parent->getRandomChild(seed);

    // addr of child2 == returned pointer
    ASSERT_EQ(child2, randomKid);
}

TEST(alterScore, pos) {
    team t;
    GameNode* node = initialiseTree(t, t);

    ASSERT_EQ(0, node->getScore());

    node->alterScore(1);

    ASSERT_EQ(1, node->getScore());
}

TEST(alterScore, neg) {
    team t;
    GameNode* node = initialiseTree(t, t);

    ASSERT_EQ(0, node->getScore());

    node->alterScore(-1);

    ASSERT_EQ(-1, node->getScore());
}

TEST(evaluate, oneToOne) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(parent, 0, t, t);

    child->alterScore(1);

    double value = child->evaluate(0);
    ASSERT_EQ(1, value);
}

TEST(removeChild, onlyChild) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(parent, 1, t, t);

    ASSERT_EQ(1, parent->getChildren().size());

    parent->removeChild(child);

    ASSERT_EQ(0, parent->getChildren().size());

    ASSERT_EQ(nullptr, child->getParent());
}

TEST(removeChild, siblings) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child1 = parent->addChild(parent, 1, t, t);

    GameNode* child2 = parent->addChild(parent, 1, t, t);

    ASSERT_EQ(2, parent->getChildren().size());

    parent->removeChild(child1);

    ASSERT_EQ(1, parent->getChildren().size());

    ASSERT_EQ(nullptr, child1->getParent());
    ASSERT_EQ(parent, child2->getParent());
}

TEST(changeRoot, onlyChild) {
    team t;
    GameNode* root = initialiseTree(t, t);

    GameNode* child = root->addChild(root, 1, t, t);

    GameNode* newRoot = changeRoot(root, child);

    ASSERT_EQ(child, newRoot);
    ASSERT_EQ(nullptr, newRoot->getParent());
}
