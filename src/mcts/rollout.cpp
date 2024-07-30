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

bool simulate(GameNode* node, bool quiet) {
    team white = node->getWhite();
    team black = node->getBlack();
    bool turn = node->getTurn();
    std::optional<bool> winner = std::nullopt;
    int ply;
    while (!winner.has_value()) {
        winner = getWinner(white, black);
        std::optional<bitboard> randomMove = std::nullopt;
        int randomPieceIndex;
        std::random_device rd;
        while (!randomMove.has_value()) {
            randomPieceIndex = rd() % 6;  // TODO better method
            randomMove = getRandomMove(white, black, turn, randomPieceIndex);
        }
        std::pair<team, team> newBoards = makeSimulatedMove(
            white, black, randomMove.value(), randomPieceIndex, turn);

        white = newBoards.first;
        black = newBoards.second;

        if (!quiet) {
            std::cout << gameStateToString(white, black) << std::endl;
        }

        turn = !turn;
    }
    winner = winner.value();
    if (node->getTurn() == winner.value()) {
        node->incrWins();
    }
    return winner.value();
}
