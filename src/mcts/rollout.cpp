#include "mcts/rollout.h"

#include <assert.h>

#include <iostream>
#include <optional>
#include <random>
#include <utility>
#include <vector>

#include "game/chess.h"
#include "game/moves.h"
#include "utils.h"

std::pair<bitboard, int> getRandomLegalMove(
    std::vector<std::pair<bitboard, int>> moves, bool turn) {
    std::random_device rd;

    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    std::size_t randomMoveIndex = dist(rng);

    return moves.at(randomMoveIndex);
}

std::vector<std::pair<bitboard, int>> getAllLegalMoves(team& white, team& black,
                                                       bool colour) {
    std::vector<std::pair<bitboard, int>> moves;
    for (int piece = 0; piece < 6; piece++) {
        std::vector<bitboard> thisMoves =
            legalMovesFromIndex(piece, white, black, colour);
        for (bitboard move : thisMoves) {
            moves.emplace_back(move, piece);
        }
    }
    return moves;
}

std::optional<bitboard> getRandomMove(team& white, team& black, bool turn,
                                      int pieceIndex) {
    std::random_device rd;
    std::vector<bitboard> moves =
        pseudoLegalFromIndex(pieceIndex, white, black, turn);
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    std::size_t randomMoveIndex = dist(rng);

    if (moves.size() == 0) {
        return std::nullopt;
    }

    return moves.at(randomMoveIndex);
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

std::optional<bool> simulate(GameNode* node, bool quiet) {
    // assert(node->getParent() != nullptr);
    team white = node->getWhite();
    team black = node->getBlack();
    assert(white.at(5) != 0);
    assert(black.at(5) != 0);
    bool turn = node->getTurn();
    int halfMoveClock = 0;
    while (true) {
        if (!quiet) {
            std::cout << gameStateToString(white, black) << std::endl;
        }
        // Black wins
        if (isMated(white, black, true)) {
            bool winner = false;
            // node->getTurn = player to move now. So parent is winner
            return winner;
        }
        // White wins
        if (isMated(white, black, false)) {
            bool winner = true;
            // node->getTurn = player to move now. So prev is winner
            return winner;
        }

        std::vector<std::pair<bitboard, int>> legalMoves =
            getAllLegalMoves(white, black, turn);
        // No legals: stalemate
        if (legalMoves.empty()) {
            return std::nullopt;
        }

        auto [randomMove, pieceIdx] = getRandomLegalMove(legalMoves, turn);
        auto [newWhite, newBlack] =
            makeMove(white, black, randomMove, pieceIdx, turn);

        int oldPly = halfMoveClock;
        // If there is no capture, increment half move clock
        if (turn) {
            if (!checkIfCapture(black, newBlack)) halfMoveClock++;
        } else {
            if (!checkIfCapture(white, newWhite)) halfMoveClock++;
        }
        if (oldPly == halfMoveClock) halfMoveClock = 0;

        // Stalemate
        if (halfMoveClock >= 100) {
            return std::nullopt;
        }

        white = newWhite;
        black = newBlack;

        turn = !turn;
    }
}
