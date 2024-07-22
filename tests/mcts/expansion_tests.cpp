#include <gtest/gtest.h>

#include <vector>

#include "game/inits.h"
#include "mcts/expansion.h"
#include "mcts/gametree.h"
#include "utils.h"

TEST(expansion, soloPawn) {
    // White have a single pawn
    team white = {0x8, 0, 0, 0, 0, 0};
    team black = {0x0800000000000000, 0, 0, 0, 0, 0};
    GameNode* node = initialiseTree(white, black);

    ASSERT_EQ(0, node->getChildren().size());

    expansion(node);

    ASSERT_EQ(1, node->getChildren().size());

    GameNode* child = node->getChildren()[0];

    expansion(node->getChildren()[0]);

    ASSERT_EQ(1, node->getChildren().size());
    ASSERT_EQ(1, node->getChildren()[0]->getChildren().size());
}

TEST(expansion, startGame) {
    // Starting positions
    team white = {whitePawnInit,   whiteHorseInit, whiteCastleInit,
                  whiteBishopInit, whiteQueenInit, whiteKingInit};
    team black = {blackPawnInit,   blackHorseInit, blackCastleInit,
                  blackBishopInit, blackQueenInit, blackKingInit};

    GameNode* node = initialiseTree(white, black);

    ASSERT_EQ(0, node->getChildren().size());

    expansion(node);
    // Each pawn has two possible moves, plus each horse has one possible moves
    ASSERT_EQ(20, node->getChildren().size());
}
