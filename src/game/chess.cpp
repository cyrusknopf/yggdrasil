#include "game/chess.h"

#include <optional>
#include <utility>
#include <vector>

#include "game/inits.h"
#include "game/moves.h"
#include "mcts/rollout.h"
#include "utils.h"

std::pair<team, team> initGame() {
    team whiteBitboards = {whitePawnInit,   whiteHorseInit, whiteCastleInit,
                           whiteBishopInit, whiteQueenInit, whiteKingInit};

    team blackBitboards = {blackPawnInit,   blackHorseInit, blackCastleInit,
                           blackBishopInit, blackQueenInit, blackKingInit};

    return std::make_pair(whiteBitboards, blackBitboards);
}

bool noLegalMoves(team& own, team& opponent, bool turn) {
    for (int piece = 0; piece < 6; ++piece) {
        std::vector<bitboard> moves =
            pseudoLegalFromIndex(piece, own, opponent, turn);
        for (bitboard move : moves) {
            std::pair<team, team> newTeams =
                makeSimulatedMove(own, opponent, move, piece, turn);
            if (!isOwnKingInCheck(newTeams.first, newTeams.second, turn)) {
                return false;  // Legal move found
            }
        }
    }
    return true;  // No legal moves
}

std::optional<bool> getWinner(team& white, team& black, int ply) {
    // If neither are in check, they can't be in check mate
    if (!isOwnKingInCheck(white, black, true) &&
        !isOwnKingInCheck(black, white, false))
        return std::nullopt;

    // White in check:
    else if (isOwnKingInCheck(white, black, true)) {
        // Check all moves going backwards, first checking if king can move
        for (int piece = 5; piece > 0; piece--) {
            std::vector<bitboard> moves =
                pseudoLegalFromIndex(piece, white, black, true);
            for (bitboard move : moves) {
                std::pair<team, team> newTeams =
                    makeSimulatedMove(white, black, move, piece, true);
                if (!isOwnKingInCheck(newTeams.first, newTeams.second, true)) {
                    return std::nullopt;
                }
            }
        }
        // We checked all moves, in every case the king is in check: checkmate
        return false;

    }
    // Black in check:
    else {
        // Check all moves going backwards, first checking if king can move
        for (int piece = 5; piece > 0; piece--) {
            std::vector<bitboard> moves =
                pseudoLegalFromIndex(piece, black, white, false);
            for (bitboard move : moves) {
                std::pair<team, team> newTeams =
                    makeSimulatedMove(white, black, move, piece, false);
                if (!isOwnKingInCheck(newTeams.second, newTeams.first, false)) {
                    return std::nullopt;
                }
            }
        }
        // We checked all moves, in every case the king is in check: checkmate
        return true;
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
