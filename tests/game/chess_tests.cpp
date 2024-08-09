#include <game/inits.h>
#include <gtest/gtest.h>

#include "game/chess.h"
#include "utils.h"

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
    team white = {WhitePawns,      whiteHorseInit, WhiteCastles,
                  whiteBishopInit, whiteQueenInit, whiteKingInit};

    bitboard BlackPawns = blackPawnInit ^ coordinateToState("f7");
    BlackPawns |= coordinateToState("f6");
    bitboard BlackKing = coordinateToState("e6");
    team black = {BlackPawns,      blackHorseInit, blackCastleInit,
                  blackBishopInit, blackQueenInit, BlackKing};

    ASSERT_FALSE(isMated(white, black, false));
}

TEST(isMated, endGame1) {
    team white = {70940428800, 72, 128, 36, 8388608, 536870912};
    team black = {88665322160129,         4755801206503243776,
                  9295429630892703744ULL, 288371113640067072,
                  1152921504606846976,    576460752303423488};

    ASSERT_TRUE(isMated(white, black, true));
    ASSERT_FALSE(isMated(white, black, false));
}

TEST(isMated, endGame2) {
    team white = {0, 0, 9223372036854775808ULL, 0, 0, 35184372088832};
    team black = {1, 0, 0, 0, 0, 2305843009213693952};

    ASSERT_FALSE(isMated(white, black, true));
    ASSERT_TRUE(isMated(white, black, false));
}

TEST(isMated, endGame3) {
    team white = {4294967296, 2097152, 8192, 0, 256, 2048};
    team black = {0, 0, 0, 0, 0, 128};

    ASSERT_FALSE(isMated(white, black, true));
    ASSERT_FALSE(isMated(white, black, false));
}
