#include <game/chess.h>
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

TEST(expansion, terminal) {
    team white = {549755813888, 0, 4294967298, 0, 0, 4611686018427387904};
    team black = {0, 0, 0, 0, 0, 281474976710656};

    GameNode* terminalState = new GameNode(nullptr, 0, white, black, false);
    ASSERT_EQ(0, terminalState->getChildren().size());
    expansion(terminalState);
    ASSERT_EQ(0, terminalState->getChildren().size());
}

TEST(expansion, mateIn1) {
    team white = {0, 0, coordinateToState("a7"), 0, 0, 35184372088832};
    team black = {0, 0, 0, 0, 0, 2305843009213693952};

    GameNode* parent = new GameNode(nullptr, 0, white, black, true);
    ASSERT_EQ(0, parent->getChildren().size());
    expansion(parent);
    std::vector<GameNode*> children = parent->getChildren();
    // Castle moving north : mate
    GameNode* mate = children.at(0);
    ASSERT_TRUE(mate->getTerminal());
    for (int i = 1; i < children.size(); i++) {
        ASSERT_FALSE(children.at(i)->getTerminal());
    }
}

TEST(expansion, promotion) {
    bitboard whitePawn = coordinateToState("a7");
    bitboard whiteKing = coordinateToState("h1");
    bitboard blackKing = coordinateToState("b1");

    team white = {whitePawn, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, 0, 0, 0, blackKing};

    GameNode* node = new GameNode(nullptr, 0, white, black, true);

    ASSERT_EQ(0, node->getChildren().size());

    expansion(node);

    std::vector<GameNode*> children = node->getChildren();
    // 1 pawn push with four possible promotions. 3 moves for king
    ASSERT_EQ((1 * 4) + 3, children.size());

    for (int i = 0; i < 4; i++) {
        GameNode* promote = children.at(i);
        // Assert the move is the result of pawn push
        ASSERT_EQ(promote->getMove(), coordinateToState("a8"));
        // Assert the pawn has been promoted i.e. removed
        ASSERT_EQ(promote->getWhite().at(0), 0);
        // Assert the piece has taken the pawn's place
        // (piece index = i + 1)i.e 1st promotion(index 0)=horse(piece index 1))
        ASSERT_EQ(promote->getWhite().at(i + 1), coordinateToState("a8"));
    }
}
