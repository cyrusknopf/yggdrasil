#include <gtest/gtest.h>
#include <mcts/gametree.h>
#include <mcts/rollout.h>

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

TEST(getBetween, edgeCase1) {
    bitboard whiteKing = 8;
    bitboard blackQueen = 16777216;
    bitboard ownState = 2223012799;
    bitboard oppState = 17291298090422108160ULL;
    bitboard btwn = getBetween(whiteKing, blackQueen);
    ASSERT_EQ(0, btwn & (ownState | oppState));
}

TEST(getChildren, edgeCase1) {
    team white = {70934096640, 134217730, 129, 36, 16, 8};
    team black = {34766557670277120,      4755801206503243776,
                  9295429630892703744ULL, 2594073385365405696,
                  1152921504606846976,    17592186044416};
    GameNode* parent = new GameNode(nullptr, 134217730, white, black, false);
    auto children = getAllLegalMoves(white, black, false);
    ASSERT_EQ(0, children.size());
}

TEST(legalMoves, edgeCaseDoubleMove) {
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

    auto moves = getAllLegalMoves(white, black, false);
    ASSERT_EQ(1, moves.size());
    auto [move, idx] = moves.at(0);
    ASSERT_EQ(coordinateToState("d7"), move);
}

TEST(getCastles, TODO) { FAIL(); }

TEST(getEnpassants, TODO) { FAIL(); }
