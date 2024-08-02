#include <game/inits.h>
#include <gtest/gtest.h>

#include "game/chess.h"

TEST(isMated, whiteMated) {
    bitboard whiteKing = coordinateToState("a1");
    bitboard blackCastles = coordinateToState("a3") | coordinateToState("c1");
    bitboard blackBishop = coordinateToState("c3");
    team white = {0, 0, 0, 0, 0, whiteKing};
    team black = {0, 0, blackCastles, blackBishop, 0, 0};

    bool mated = isMated(white, black, true);

    ASSERT_EQ(true, mated);
}

TEST(isMated, realCase) {
    bitboard WhitePawns = whitePawnInit ^ coordinateToState("a2");
    WhitePawns |= coordinateToState("a4");
    bitboard WhiteCastles = whiteCastleInit ^ coordinateToState("a1");
    WhiteCastles |= coordinateToState("e2");
    team white = {WhitePawns, whiteHorseInit, WhiteCastles, whiteBishopInit, whiteQueenInit, whiteKingInit};

    bitboard BlackPawns = blackPawnInit ^ coordinateToState("f7");
    BlackPawns |= coordinateToState("f6");
    bitboard BlackKing=  coordinateToState("e6");
    team black = {BlackPawns, blackHorseInit, blackCastleInit, blackBishopInit, blackQueenInit, BlackKing};

    ASSERT_FALSE(isMated(white,black,false));
}
