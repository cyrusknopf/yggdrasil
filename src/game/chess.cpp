#include "game/chess.h"
#include "game/inits.h"
#include "utils.h"
#include <utility>

std::pair<team, team> initGame() {
    team whiteBitboards = {whitePawnInit,   whiteHorseInit, whiteCastleInit,
                           whiteBishopInit, whiteQueenInit, whiteKingInit};

    team blackBitboards = {blackPawnInit,   blackHorseInit, blackCastleInit,
                           blackBishopInit, blackQueenInit, blackKingInit};

    return std::make_pair(whiteBitboards, blackBitboards);
}

bitboard getGameState(team &white, team &black) {
    return getGameState(white, black, true) | getGameState(white, black, false);
}

bitboard getGameState(team &white, team &black, bool colour) {
    bitboard state = 0;
    if (colour) {
        for (auto &board : white) {
            state |= board;
        }
    } else {
        for (auto &board : black) {
            state |= board;
        }
    }
    return state;
}

bitboard getTeamState(team &pieces) {
    bitboard state = 0;
    for (auto &piece : pieces) {
        state |= piece;
    }
    return state;
}
