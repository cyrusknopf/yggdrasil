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

std::optional<bitboard> getRandomLegalMove(team& white, team& black, bool turn,
                                           int pieceIndex) {
    std::random_device rd;
    std::vector<bitboard> moves =
        legalMovesFromIndex(pieceIndex, white, black, turn);

    if (moves.size() == 0) {
        return std::nullopt;
    }

    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    std::size_t randomMoveIndex = dist(rng);

    return moves[randomMoveIndex];
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

    return moves[randomMoveIndex];
}

std::pair<team, team> makeSimulatedMove(team& white, team& black, bitboard move,
                                        int index, bool turn) {
    team own;
    team opp;

    if (turn) {
        own = white;
        opp = black;
    } else {
        own = black;
        opp = white;
    }

    // Get the square which the moving piece moves to
    bitboard destinationSquare = ~(~move | own.at(index));
    if (destinationSquare == 0) {
    }
    // Determine if the enemy is on the moved to piece i.e. there is a capture
    std::pair<bitboard, int> captureInfo = findPiece(destinationSquare, opp);
    int capturedIdx = captureInfo.second;
    // If there is a capture, perform the capture
    if (capturedIdx != -1) {
        opp[capturedIdx] = performCapture(opp[capturedIdx], destinationSquare);
    };
    // Update the move mode
    own[index] = move;
    if (turn)
        return std::make_pair(own, opp);
    else
        return std::make_pair(opp, own);
}

bool checkIfCapture(team& oldBoards, team& newBoards) {
    for (int i = 0; i < 6; i++) {
        if (oldBoards.at(i) != newBoards.at(i)) return true;
    }
    return false;
}

std::optional<bool> simulate(GameNode* node, bool quiet) {
    team white = node->getWhite();
    team black = node->getBlack();
    if (white.at(5) == 0) {
        assert(white.at(5) != 0);
    } else if (black.at(5) == 0) {
        assert(black.at(5) != 0);
    }
    bool turn = node->getTurn();
    int ply = 0;
    while (true) {
        if (!quiet) {
            std::cout << gameStateToString(white, black) << std::endl;
        }
        // Black wins
        if (isMated(white, black, true)) {
            bool winner = false;
            if (node->getTurn() == winner) node->incrWins();
            return winner;
        }
        // White wins
        if (isMated(white, black, false)) {
            bool winner = true;
            if (node->getTurn() == winner) node->incrWins();
            return winner;
        }

        std::vector<std::pair<bitboard, int>> legalMoves =
            getAllLegalMoves(white, black, turn);
        // No legals: stalemate
        if (legalMoves.empty()) return std::nullopt;
        std::random_device rd;
        const int randomIdx = rd() % legalMoves.size();  // TODO better method
        const bitboard randomMove = legalMoves.at(randomIdx).first;
        int pieceIdx = legalMoves.at(randomIdx).second;
        std::pair<team, team> newBoards =
            makeSimulatedMove(white, black, randomMove, pieceIdx, turn);

        team newWhite = newBoards.first;
        team newBlack = newBoards.second;

        int oldPly = ply;
        // If there is no capture, increment ply
        if (turn) {
            if (!checkIfCapture(black, newBlack)) ply++;
        } else {
            if (!checkIfCapture(white, newWhite)) ply++;
        }
        if (oldPly == ply) ply = 0;

        if (ply >= 100) return std::nullopt;

        white = newWhite;
        black = newBlack;

        turn = !turn;
    }
}
