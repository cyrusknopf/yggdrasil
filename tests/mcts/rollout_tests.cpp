#include <gtest/gtest.h>

#include <vector>
#include <game/moves.h>

#include "game/chess.h"
#include "game/inits.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "utils.h"

TEST(makeSimulatedMove, capture) {
    // White to move
    bool turn = true;
    // White king at a2
    team white = {0, 0, 0, 0, 0, 0x8000};
    // Black king at a3
    team black = {0, 0, 0, 0, 0, 0x800000};
    // Move to a3
    bitboard captureMove = 0x800000;
    // King is moving
    int idx = 5;

    std::pair<team, team> newBoards =
        makeSimulatedMove(white, black, captureMove, idx, turn);

    // Black king should've been captured
    ASSERT_EQ(0, newBoards.second.at(5));
    // White king should be in new location
    ASSERT_EQ(captureMove, newBoards.first.at(5));
}

TEST(simulate, blackWin) {
    bitboard whiteKing = coordinateToState("a1");
    bitboard blackCastles = coordinateToState("a3") | coordinateToState("c1");
    bitboard blackBishop = coordinateToState("c3");
    team white = {0, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, blackCastles, blackBishop, 0, 0};

    GameNode* root = initialiseTree(white, black);

    std::optional<bool> res = simulate(root, true);

    ASSERT_EQ(false, res);
}

TEST(simulate, whiteWin) {
    bitboard blackKing = coordinateToState("a1");
    bitboard whiteCastles = coordinateToState("a3") | coordinateToState("c1");
    bitboard whiteBishop = coordinateToState("c3");
    team black = {0, 0, 0, 0, 0, blackKing};
    team white = {0, 0, whiteCastles, whiteBishop, 0, 0};

    GameNode* root = initialiseTree(white, black);
    root->nextTurn();

    std::optional<bool> res = simulate(root, true);

    ASSERT_EQ(true, res);
}

TEST(getAllLegalMoves, pawn) {
    bitboard whitePawn = coordinateToState("a2");
    team white = {whitePawn, 0, 0, 0, 0, 0};
    team black = {0, 0, 0, 0, 0, 0};
    std::vector<std::pair<bitboard, int>> moves =
        getAllLegalMoves(white, black, true);
    ASSERT_EQ(2, moves.size());
    ASSERT_EQ(0, moves.at(0).second);
    ASSERT_EQ(0, moves.at(1).second);
}


TEST(getAllLegalMoves, edgeCase2) {
    team white = {2147516160, 8388610, 129, 36, 16, 8};
    team black = {69533115340554240, 4755801206503243776, 9295429630892703744, 2594073385365405696, 16777216, 576460752303423488};
    ASSERT_FALSE(isOwnKingInCheck(white, black, true));
    auto moves = getAllLegalMoves(white, black, true);
}

TEST(getAllLegalMoves, edgeCase3) {
    team white = {549755838208, 8454144,129,36, 16, 8 };
    team black = {71776119061217280, 144115188075864064, 9295429630892703744, 2594073385365405696, 1152921504606846976, 576460752303423488};
    ASSERT_TRUE(isOwnKingInCheck(white, black, true));
}

TEST(getAllLegalMoves, edgeCase4) {
    team white = {2147512064, 66, 129, 36,2251799813685248, 8 };
    team black = {33215696519299072, 144115188344291328, 108086391056891904, 2594073385365405696, 1152921504606846976, 576460752303423488};
    std::vector<std::pair<bitboard, int>> legalMoves = getAllLegalMoves(white, black, false);
}