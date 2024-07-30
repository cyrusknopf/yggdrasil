#include "mcts/rollout.h"

#include <assert.h>

#include <iostream>
#include <optional>
#include <random>
#include <utility>

#include "game/moves.h"
#include "utils.h"

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
        std::cout << "move: " << move << std::endl;
        std::cout << "own.at(" << index << "): " << own.at(index) << std::endl;
        std::cout << "move: " << move << std::endl;
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
    bool turn = node->getTurn();
    int ply;
    while (true) {
        // Black wins
        if (white.at(5) == 0) {
            bool winner = false;
            if (node->getTurn() == winner) {
                node->incrWins();
            }
            return winner;
        }
        // White wins
        if (black.at(5) == 0) {
            bool winner = true;
            if (node->getTurn() == winner) {
                node->incrWins();
            }
            return winner;
        }

        std::optional<bitboard> randomMove = std::nullopt;
        int randomPieceIndex;
        std::random_device rd;
        while (!randomMove.has_value()) {
            randomPieceIndex = rd() % 6;  // TODO better method
            randomMove = getRandomMove(white, black, turn, randomPieceIndex);
        }
        std::pair<team, team> newBoards = makeSimulatedMove(
            white, black, randomMove.value(), randomPieceIndex, turn);

        team newWhite = newBoards.first;
        team newBlack = newBoards.second;

        // If there is no capture, increment ply
        if (!checkIfCapture(white, newWhite) &&
            !checkIfCapture(black, newBlack))
            ply++;
        else
            ply = 0;  // Else reset it

        if (!quiet) {
            std::cout << gameStateToString(white, black) << std::endl;
        }

        if (ply >= 100) return std::nullopt;

        turn = !turn;
    }
}
