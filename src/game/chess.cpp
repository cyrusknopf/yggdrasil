#include "game/chess.h"

#include <mcts/rollout.h>

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
    // Check if each piece is the same before and after
    for (int i = 0; i < 6; i++) {
        if (oldBoards.at(i) != newBoards.at(i)) return true;
    }
    return false;
}

bool isMated(team& white, team& black, bool colour) {
    team own = colour ? white : black;
    team opp = colour ? black : white;

    // If not in check, cannot be mated
    if (!isOwnKingInCheck(own, opp, colour)) return false;
    // Check each piece's possible moves to see if we can get out of check
    for (int piece = 5; piece > 0; piece--) {
        for (bitboard move : legalMovesFromIndex(piece, white, black, colour)) {
            auto [newWhite, newBlack] =
                makeMove(white, black, move, piece, colour);
            team tempOwn = colour ? newWhite : newBlack;
            team tempOpp = colour ? newBlack : newWhite;
            // If we can get out of check, then not mated
            if (!isOwnKingInCheck(tempOwn, tempOpp, colour)) return false;
        }
    }
    // Otherwise mated
    return true;
}

// TODO refactor to be consistent with the fact that nullopt is used for
// stalemate
std::optional<bool> getWinner(team& white, team& black) {
    // Black wins
    if (isMated(white, black, true)) return false;

    // White wins
    else if (isMated(white, black, false))
        return true;
    else
        return std::nullopt;
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

std::pair<team, team> makeMove(team& white, team& black, bitboard move,
                               int index, bool turn) {
    team own = turn ? white : black;
    team opp = turn ? black : white;

    team newOwn = own;
    team newOpp = opp;

    // Get the square which the moving piece moves to
    bitboard destinationSquare = ~(~move | own.at(index));
    // Determine if the enemy is on the moved to piece i.e. there is a capture
    auto [captureInfo, capturedIdx] = findPiece(destinationSquare, opp);
    // If there is a capture, perform the capture
    if (capturedIdx != -1) {
        newOpp[capturedIdx] =
            performCapture(newOpp[capturedIdx], destinationSquare);
    };
    // Update the move mode
    newOwn[index] = move;
    if (turn)
        return std::make_pair(newOwn, newOpp);
    else
        return std::make_pair(newOpp, newOwn);
}
