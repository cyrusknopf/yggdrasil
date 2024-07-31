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

bool checkIfCapture(team& oldBoards, team& newBoards) {
    for (int i = 0; i < 6; i++) {
        if (oldBoards.at(i) != newBoards.at(i)) return true;
    }
    return false;
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

std::optional<bool> getWinner(team& white, team& black) {
    // Black wins
    if (isMated(white, black, true)) {
        bool winner = false;
        return winner;
    }
    // White wins
    if (isMated(white, black, false)) {
        bool winner = true;
        return winner;
    } else {
        return std::nullopt;
    }
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
