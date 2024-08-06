#include <game/moves.h>
#include <gtest/gtest.h>

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

TEST(simulate, blackMated) {
    bitboard whiteKing = 0x0000000000000040;
    bitboard whiteCastle = 0x0080000000000000;

    bitboard blackKing = 0x0000000000000080;

    team white = {0, 0, whiteCastle, 0, 0, whiteKing};
    team black = {0, 0, 0, 0, 0, blackKing};

    GameNode node = GameNode(nullptr, 0, white, black, false);

    std::optional<bool> res = simulate(&node, true);

    ASSERT_FALSE(res);
}

TEST(simulate, whiteMated) {
    bitboard blackKing = coordinateToState("g1");
    bitboard blackHorse = coordinateToState("e7");
    bitboard blackCastle = coordinateToState("e3");

    bitboard whitePawn = coordinateToState("g7");
    bitboard whiteKing = coordinateToState("h7");

    team white = {whitePawn, 0, 0, 0, 0, whiteKing};
    team black = {0, blackHorse, blackCastle, 0, 0, blackKing};

    GameNode node = GameNode(nullptr, 0, white, black, false);

    std::optional<bool> res = simulate(&node, true);

    ASSERT_FALSE(res);
}

TEST(simulate, doubleMove) {
    bitboard whitePawn = 0;
    whitePawn |= coordinateToState("a4");
    whitePawn |= coordinateToState("b2");
    whitePawn |= coordinateToState("c2");
    whitePawn |= coordinateToState("d2");
    whitePawn |= coordinateToState("e4");
    whitePawn |= coordinateToState("f2");
    whitePawn |= coordinateToState("h2");
    whitePawn |= coordinateToState("h3");
    bitboard whiteHorse = 0;
    whiteHorse |= coordinateToState("b1");
    whiteHorse |= coordinateToState("f3");
    bitboard whiteCastle = 0;
    whiteCastle |= coordinateToState("f5");
    bitboard whiteQueen = coordinateToState("f8");
    team white = {whitePawn,       whiteHorse, whiteCastle,
                  whiteBishopInit, whiteQueen, whiteKingInit};

    bitboard blackPawns = 0;
    blackPawns |= coordinateToState("a7");
    blackPawns |= coordinateToState("b7");
    blackPawns |= coordinateToState("c7");
    blackPawns |= coordinateToState("d3");
    blackPawns |= coordinateToState("f4");
    bitboard blackCastle = coordinateToState("a8");
    bitboard blackHorse = coordinateToState("b8");
    blackHorse |= coordinateToState("e7");
    bitboard blackBishop = coordinateToState("c8");
    team black = {blackPawns,  blackHorse,     blackCastle,
                  blackBishop, blackQueenInit, blackKingInit};

    GameNode node = GameNode(nullptr, 0, white, black, false);

    std::optional<bool> res = simulate(&node, true);
}
