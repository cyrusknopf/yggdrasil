#include "game/chess.h"

#include <utility>

#include "game/inits.h"
#include "game/moves.h"
#include "utils.h"

std::pair<team, team> initGame() {
    team whiteBitboards = {whitePawnInit,   whiteHorseInit, whiteCastleInit,
                           whiteBishopInit, whiteQueenInit, whiteKingInit};

    team blackBitboards = {blackPawnInit,   blackHorseInit, blackCastleInit,
                           blackBishopInit, blackQueenInit, blackKingInit};

    return std::make_pair(whiteBitboards, blackBitboards);
}

bool isMated(team& white, team& black, bool colour) {
    team own;
    team opp;
    if (colour) {
        own = white;
        opp = black;
    } else {
        own = black;
        opp = white;
    }

    if (!isOwnKingInCheck(own, opp, colour)) return false;
    for (int piece = 5; piece > 0; piece--) {
        for (bitboard move :
             pseudoLegalFromIndex(piece, white, black, colour)) {
            team tempOwn = own;
            team tempOpp = opp;
            tempOwn[piece] = move;
            if (!isOwnKingInCheck(tempOwn, tempOpp, colour)) return false;
        }
    }
    return true;
}

bitboard getGameState(team& white, team& black) {
    return getGameState(white, black, true) | getGameState(white, black, false);
}

bitboard getGameState(team& white, team& black, bool colour) {
    bitboard state = 0;
    if (colour) {
        for (auto& board : white) {
            state |= board;
        }
    } else {
        for (auto& board : black) {
            state |= board;
        }
    }
    return state;
}

bitboard getTeamState(team& pieces) {
    bitboard state = 0;
    for (auto& piece : pieces) {
        state |= piece;
    }
    return state;
}
