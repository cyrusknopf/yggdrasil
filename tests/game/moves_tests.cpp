#include <gtest/gtest.h>

#include <vector>

#include "game/inits.h"
#include "game/moves.h"
#include "utils.h"

TEST(pawnPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = pawnPseudoLegalMoves(0, 0, state, true);

    ASSERT_EQ(1, moves.size());
}

TEST(pawnPseudoLegalMoves, start) {
    bitboard state = whitePawnInit;
    std::vector<bitboard> moves = pawnPseudoLegalMoves(0, 0, state, true);

    ASSERT_EQ(16, moves.size());
}

TEST(pawnPseudoLegalMoves, jumpOverFriend) {
    bitboard pawnState = 0x0000000000000008;
    bitboard horseState = 0x000000000000800;

    std::vector<bitboard> moves =
        pawnPseudoLegalMoves(horseState, 0, pawnState, true);

    ASSERT_EQ(0, moves.size());
}
TEST(horsePseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = horsePseudoLegalMoves(0, 0, state);

    ASSERT_EQ(8, moves.size());
}

TEST(castlePseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = castlePseudoLegalMoves(0, 0, state);
}

TEST(bishopPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = bishopPseudoLegalMoves(0, 0, state);

    ASSERT_EQ(13, moves.size());
}

TEST(queenPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = queenPseudoLegalMoves(0, 0, state);

    ASSERT_EQ(27, moves.size());
}

TEST(kingPseudoLegalMoves, e4) {
    bitboard state = 0x0000000008000000;
    std::vector<bitboard> moves = kingPseudoLegalMoves(0, 0, state);

    ASSERT_EQ(8, moves.size());
}

TEST(pseudoLegalFromIndex, pawn_e4) {
    bitboard state = 0x0000000008000000;
    team white = {state, 0, 0, 0, 0, 0};
    team black = {0, 0, 0, 0, 0, 0};

    std::vector<bitboard> idxMoves =
        pseudoLegalFromIndex(0, white, black, true);
    ASSERT_EQ(1, idxMoves.size());

    std::vector<bitboard> moves = pawnPseudoLegalMoves(0, 0, state, true);

    ASSERT_EQ(idxMoves.at(0), moves.at(0));
}

TEST(isOwnKingInCheck, knightCheck) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingKnight = coordinateToState("d3");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, attackingKnight, 0, 0, 0, 0};

    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, castleCheck) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingCastle = coordinateToState("h1");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, attackingCastle, 0, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, castleCheckBlockedOwn) {
    bitboard ownKing = coordinateToState("e1");
    // Pawn blocking attacking castle
    bitboard ownPawn = coordinateToState("f1");
    bitboard attackingCastle = coordinateToState("h1");
    team white = {ownPawn, 0, 0, 0, 0, ownKing};
    team black = {0, 0, attackingCastle, 0, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, castleCheckBlockedOpp) {
    bitboard ownKing = coordinateToState("e1");
    // Pawn blocking attacking castle
    bitboard oppPawn = coordinateToState("f1");
    bitboard attackingCastle = coordinateToState("h1");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {oppPawn, 0, attackingCastle, 0, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, castleCheckOneBlockedOneCheck) {
    bitboard ownKing = coordinateToState("e1");
    // Pawn blocking attacking castle
    bitboard ownPawn = coordinateToState("f1");
    bitboard attackingCastles =
        coordinateToState("h1") | coordinateToState("e8");
    team white = {ownPawn, 0, 0, 0, 0, ownKing};
    team black = {0, 0, attackingCastles, 0, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, bishopCheck) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingBishop = coordinateToState("b4");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, attackingBishop, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}
