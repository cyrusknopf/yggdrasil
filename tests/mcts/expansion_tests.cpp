#include <gtest/gtest.h>

#include <iostream>

#include "game/driver.h"
#include "mcts/expansion.h"
#include "mcts/gametree.h"

TEST(expansion, soloPawn) {
    // White have a single pawn
    team white = {0x8, 0, 0, 0, 0, 0};
    team black = {0, 0, 0, 0, 0, 0};
    GameNode node = GameNode(nullptr, 0, white, black, true);
    ASSERT_EQ(0, node.getChildren().size());

    GameNode* newNode = expansion(&node);

    node.addChild(newNode);

    ASSERT_EQ(1, node.getChildren().size());

    GameNode* child = node.getChildren()[0];

    std::cout << "in expansion" << std::endl;
    std::cout << gameStateToString(child->getWhite(), child->getBlack());

    /*
    expansion(node.getChildren()[0]);
    std::cout << "second expand complete" << std::endl;

    ASSERT_EQ(1, node.getChildren().size());
    ASSERT_EQ(2, node.getChildren()[0]->getChildren().size());
    */
}
