#include <gtest/gtest.h>

#include <cstdlib>
#include <vector>

#include "game/chess.h"
#include "mcts/expansion.h"
#include "mcts/gametree.h"
#include "utils.h"

TEST(getChildren, onlyChild) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(1, t, t);

    std::vector<GameNode*> kids = parent->getChildren();

    ASSERT_EQ(1, kids.size());

    GameNode* kid = kids[0];

    // addr of child == returned pointer
    ASSERT_EQ(child, kid);
}

TEST(incrWins, pos) {
    team t;
    GameNode* node = initialiseTree(t, t);

    ASSERT_EQ(0, node->getWins());

    node->incrWins();

    ASSERT_EQ(1, node->getWins());
}

TEST(evaluate, oneToOne) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(0, t, t);

    child->incrWins();

    double value = child->evaluate(0);
    ASSERT_EQ(1, value);
}

TEST(removeChild, onlyChild) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child = parent->addChild(1, t, t);

    ASSERT_EQ(1, parent->getChildren().size());

    parent->removeChild(child);

    ASSERT_EQ(0, parent->getChildren().size());

    ASSERT_EQ(nullptr, child->getParent());
}

TEST(removeChild, siblings) {
    team t;
    GameNode* parent = initialiseTree(t, t);

    GameNode* child1 = parent->addChild(1, t, t);

    GameNode* child2 = parent->addChild(1, t, t);

    ASSERT_EQ(2, parent->getChildren().size());

    parent->removeChild(child1);

    ASSERT_EQ(1, parent->getChildren().size());

    ASSERT_EQ(nullptr, child1->getParent());
    ASSERT_EQ(parent, child2->getParent());
}

TEST(changeRoot, onlyChild) {
    team t;
    GameNode* root = initialiseTree(t, t);

    GameNode* child = root->addChild(1, t, t);

    auto children = root->getChildren();

    GameNode* newRoot = changeRoot(root, child);

    ASSERT_EQ(child, newRoot);
    ASSERT_EQ(nullptr, newRoot->getParent());
}

TEST(updateRootOnMove, whiteSinglePawnPush) {
    bitboard pawn = 0x0000000000000001;
    team white = {pawn, 0, 0, 0, 0, 0};
    team black = {0x08000000000000000, 0, 0, 0, 0, 0};

    GameNode* root = initialiseTree(white, black);

    expansion(root);

    // Should have one child after expansion (single pawn push)
    ASSERT_EQ(1, root->getChildren().size());

    GameNode* child = root->getChildren().at(0);

    bitboard newPawn = slideNorth(pawn);
    team newWhite = {newPawn, 0, 0, 0, 0, 0};

    GameNode* newRoot = updateRootOnMove(root, newWhite, black);

    ASSERT_EQ(child, newRoot);
}

TEST(updateRootOnMove, whiteDoublePawnPush) {
    bitboard pawn = 0x000000000000100;
    team white = {pawn, 0, 0, 0, 0, 0};
    team black = {0x08000000000000000, 0, 0, 0, 0, 0};

    GameNode* root = initialiseTree(white, black);

    expansion(root);

    // Should have two children after expansion (single and double pawn push)
    ASSERT_EQ(2, root->getChildren().size());

    // Get the second child: should be gamestate where the pawn double pushed
    GameNode* correctChild = root->getChildren().at(1);

    // Simulate gamestate where pawn double pushes
    bitboard movedPawn = slideNorth(slideNorth(pawn));
    team newWhite = {movedPawn, 0, 0, 0, 0, 0};

    // Peform update
    GameNode* newRoot = updateRootOnMove(root, newWhite, black);

    ASSERT_EQ(correctChild, newRoot);
}

// Test to check if the correct root is updated in a situation where two pieces
// can move to the same spot
TEST(updateRootOnMove, possibleDoubleMove) {
    bitboard whiteCastle = coordinateToState("a8");
    bitboard whiteQueen = coordinateToState("b7");

    bitboard blackPawns = coordinateToState("a7") | coordinateToState("b8") |
                          coordinateToState("c7") | coordinateToState("b6") |
                          coordinateToState("c6");

    team white = {0, 0, whiteCastle, 0, whiteQueen, 1};
    team black = {blackPawns, 0, 0, 0, 0, 1};
    GameNode* root = initialiseTree(white, black);
    expansion(root);

    // 2 moves for the rook + 7 for the queen (cannot move northwesterly as
    // castle is there): both surrounded by black pawns
    ASSERT_EQ(2 + 7, root->getChildren().size());
    // Check the first move is the castle eastwards capture
    // (Not necessary but in current implementation this is expected behaviour)
    GameNode* correctChild = root->getChildren().at(0);
    ASSERT_EQ(coordinateToState("b8"), correctChild->getMove());

    // Make the castle eastwards capture move
    auto [newWhite, newBlack] =
        makeMove(white, black, coordinateToState("b8"), 2, true);

    // Get the new root
    GameNode* newRoot = updateRootOnMove(root, newWhite, newBlack);

    // Ensure we the new root is the expected one
    ASSERT_EQ(correctChild, newRoot);
}

TEST(updateRootOnMove, possibleDoubleMoveSamePiece) {
    bitboard whiteCastle = coordinateToState("a8") | coordinateToState("b7");

    bitboard blackPawns = coordinateToState("a7") | coordinateToState("b8") |
                          coordinateToState("c7") | coordinateToState("b6");

    team white = {0, 0, whiteCastle, 0, 0, 1};
    team black = {blackPawns, 0, 0, 0, 0, 1};

    GameNode* root = initialiseTree(white, black);
    expansion(root);

    // 2 moves for rook a8 4 moves for rook b7
    ASSERT_EQ(2 + 4, root->getChildren().size());
    // Check the first move is the castle northwards capture
    // (Not necessary but in current implementation this is expected behaviour)
    GameNode* correctChild = root->getChildren().at(0);
    bitboard correctMove = coordinateToState("b8") | coordinateToState("a8");
    ASSERT_EQ(correctMove, correctChild->getMove());

    // Make the castle eastwards capture move
    auto [newWhite, newBlack] = makeMove(white, black, correctMove, 2, true);

    // Get the new root
    GameNode* newRoot = updateRootOnMove(root, newWhite, newBlack);

    // Ensure we the new root is the expected one
    ASSERT_EQ(correctChild, newRoot);
}
