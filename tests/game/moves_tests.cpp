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

TEST(isOwnKingInCheck, horseCheck) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingHorse = coordinateToState("d3");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, attackingHorse, 0, 0, 0, 0};

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

TEST(isOwnKingInCheck, bishopCheckBlockedOwn) {
    bitboard ownKing = coordinateToState("e1");
    bitboard ownPawn = coordinateToState("c3");
    bitboard attackingBishop = coordinateToState("b4");
    team white = {ownPawn, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, attackingBishop, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, bishopCheckBlockedOpp) {
    bitboard ownKing = coordinateToState("e1");
    bitboard oppHorse = coordinateToState("c3");
    bitboard attackingBishop = coordinateToState("b4");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, oppHorse, 0, attackingBishop, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, bishopNextSquare) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingBishop = coordinateToState("d2");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, attackingBishop, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, blackPawnWhiteKing) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingPawn = coordinateToState("d2");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {attackingPawn, 0, 0, 0, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, whitePawnBlackKing) {
    bitboard ownKing = coordinateToState("d2");
    bitboard attackingPawn = coordinateToState("e1");
    team white = {attackingPawn, 0, 0, 0, 0, 0};
    team black = {0, 0, 0, 0, 0, ownKing};
    ASSERT_EQ(true, isOwnKingInCheck(black, white, false));
}

TEST(isOwnKingInCheck, kingVsKingNorth) {
    bitboard ownKing = coordinateToState("e4");
    bitboard oppKing = coordinateToState("e3");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, 0, oppKing};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, kingVsKingSouth) {
    bitboard ownKing = coordinateToState("e4");
    bitboard oppKing = coordinateToState("e5");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, 0, oppKing};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, kingVsKingEast) {
    bitboard ownKing = coordinateToState("e4");
    bitboard oppKing = coordinateToState("d4");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, 0, oppKing};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, kingVsKingWest) {
    bitboard ownKing = coordinateToState("e4");
    bitboard oppKing = coordinateToState("f4");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, 0, oppKing};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, queenCheckDiagonal) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingQueen = coordinateToState("h4");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, attackingQueen, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, queenCheckVertical) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingQueen = coordinateToState("e8");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, attackingQueen, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, queenCheckHorizontal) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingQueen = coordinateToState("a1");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, attackingQueen, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, queenCheckBlockedOwnPiece) {
    bitboard ownKing = coordinateToState("e1");
    bitboard ownPawn = coordinateToState("d2");
    bitboard attackingQueen = coordinateToState("c3");
    team white = {ownPawn, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, attackingQueen, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, knightCheckLShape) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingKnight = coordinateToState("g2");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, attackingKnight, 0, 0, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, checkPawnNotBlocked) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingPawn = coordinateToState("d2");
    bitboard ownPawn = coordinateToState("d3");
    team white = {ownPawn, 0, 0, 0, 0, ownKing};
    team black = {attackingPawn, 0, 0, 0, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, rookCheckHorizontalBlocked) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingRook = coordinateToState("h1");
    bitboard ownKnight = coordinateToState("f1");
    team white = {0, ownKnight, 0, 0, 0, ownKing};
    team black = {0, 0, attackingRook, 0, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, rookCheckVerticalBlocked) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingRook = coordinateToState("e8");
    bitboard ownBishop = coordinateToState("e3");
    team white = {0, 0, 0, ownBishop, 0, ownKing};
    team black = {0, 0, attackingRook, 0, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, kingCheckAdjacent) {
    bitboard ownKing = coordinateToState("e4");
    bitboard oppKing = coordinateToState("e5");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, 0, oppKing};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, kingCheckDiagonal) {
    bitboard ownKing = coordinateToState("e4");
    bitboard oppKing = coordinateToState("d5");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, 0, oppKing};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, noCheckEmptyBoard) {
    bitboard ownKing = coordinateToState("e1");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, 0, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, checkFarPieces) {
    bitboard ownKing = coordinateToState("e1");
    bitboard oppBishop = coordinateToState("a5");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, 0, oppBishop, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, checkMultipleAttackers) {
    bitboard ownKing = coordinateToState("e1");
    bitboard oppRook = coordinateToState("h1");
    bitboard oppBishop = coordinateToState("a5");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, 0, oppRook, oppBishop, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, noCheckOwnPieceBlock) {
    bitboard ownKing = coordinateToState("e1");
    bitboard ownRook = coordinateToState("f1");
    bitboard oppRook = coordinateToState("h1");
    team white = {0, 0, ownRook, 0, 0, ownKing};
    team black = {0, 0, oppRook, 0, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, pawnCheckWhite) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingPawn = coordinateToState("d2");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {attackingPawn, 0, 0, 0, 0, 0};
    ASSERT_EQ(true, isOwnKingInCheck(white, black, true));
}

TEST(isOwnKingInCheck, pawnCheckBlack) {
    bitboard attackingPawn = coordinateToState("d2");
    bitboard ownKing = coordinateToState("e3");
    team white = {attackingPawn, 0, 0, 0, 0, 0};
    team black = {0, 0, 0, 0, 0, ownKing};
    ASSERT_EQ(true, isOwnKingInCheck(black, white, false));
}

TEST(isOwnKingInCheck, noCheckKnightFar) {
    bitboard ownKing = coordinateToState("e1");
    bitboard attackingKnight = coordinateToState("c6");
    team white = {0, 0, 0, 0, 0, ownKing};
    team black = {0, attackingKnight, 0, 0, 0, 0};
    ASSERT_EQ(false, isOwnKingInCheck(white, black, true));
}

TEST(legalMovesFromIndex, kingMoveIntoCastles) {
    bitboard whiteKing = coordinateToState("a1");
    bitboard attackingCastles =
        coordinateToState("b3") | coordinateToState("c2");
    team white = {0, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, attackingCastles, 0, 0, 0};
    ASSERT_EQ(0, legalMovesFromIndex(5, white, black, true).size());
}

TEST(legalMovesFromIndex, kingFreeToMove) {
    bitboard whiteKing = coordinateToState("e4");
    team white = {0, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, 0, 0, 0, 0};
    ASSERT_EQ(pseudoLegalFromIndex(5, white, black, true).size(),
              legalMovesFromIndex(5, white, black, true).size());
}
