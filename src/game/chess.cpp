#include "game/chess.h"

#include <mcts/rollout.h>

#include <utility>
#include <vector>

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

std::vector<Move> getPromotions(team& t, bool colour) {
    bitboard promotionRank;
    std::vector<Move> promotes{};
    // If checking white pawns:
    if (colour) {
        // Rank 8 for white
        promotionRank = 72057594037927936;
        // For each white pawn
        for (bitboard pawn : getAllPieces(t.at(0))) {
            // If the pawn is in rank 8
            if (pawn >= promotionRank) {
                // For knight, castle, bishop, queen
                for (int p = 1; p < 5; p++) {
                    promotes.push_back({pawn, p});
                }
            }
        }
    } else {  // Otherwise checking black pawns:
        // Rank 1 for black
        promotionRank = 128;
        // For each black pawn
        for (bitboard pawn : getAllPieces(t.at(0))) {
            // If the pawn is in rank 8
            if (pawn <= promotionRank) {
                // For knight, castle, bishop, queen
                for (int p = 1; p < 5; p++) {
                    promotes.push_back({pawn, p});
                }
            }
        }
    }
    return promotes;
}

std::pair<team, team> promotePawn(Move promotion, team& white, team& black,
                                  bool promoted) {
    // If we are promoting on white
    if (promoted) {
        team newWhite = white;
        newWhite.at(0) ^= promotion.boardState;
        newWhite.at(promotion.pieceIdx) |= promotion.boardState;
        return std::make_pair(newWhite, black);

    } else {  // Else we are promoting on black
        team newBlack = black;
        newBlack.at(0) = newBlack.at(0) ^ promotion.boardState;
        newBlack.at(promotion.pieceIdx) |= promotion.boardState;
        return std::make_pair(white, newBlack);
    }
}

bool isMated(team& white, team& black, bool colour) {
    team own = colour ? white : black;
    team opp = colour ? black : white;

    // If not in check, cannot be mated
    if (!isOwnKingInCheck(own, opp, colour)) return false;
    // Check each piece's possible moves to see if we can get out of
    // check
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
