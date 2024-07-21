#include "mcts/rollout.h"

#include <assert.h>

#include <iostream>
#include <optional>
#include <random>
#include <utility>

#include "game/driver.h"
#include "game/moves.h"
#include "utils.h"

std::optional<bitboard> getRandomMove(GameNode* node, int pieceIndex) {
    std::random_device rd;
    std::vector<bitboard> moves = pseudoLegalFromIndex(
        pieceIndex, node->getWhite(), node->getBlack(), node->getTurn());
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
    // XXX this is sometimes 0 for some reason
    bitboard destinationSquare = ~(~move | own.at(index));
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

int simulate(GameNode* node, bool quiet) {
    while (true) {
        // Black wins
        if (node->getWhite().at(5) == 0) return -1;
        // White wins
        if (node->getBlack().at(5) == 0) return 1;

        std::optional<bitboard> randomMove = std::nullopt;
        int randomPieceIndex;
        std::random_device rd;
        while (!randomMove.has_value()) {
            randomPieceIndex = rd() % 6;
            randomMove = getRandomMove(node, randomPieceIndex);
        }
        std::pair<team, team> newBoards = makeSimulatedMove(
            node->getWhite(), node->getBlack(), randomMove.value(),
            randomPieceIndex, node->getTurn());

        node->setWhite(newBoards.first);
        node->setBlack(newBoards.second);

        if (!quiet) {
            std::cout << gameStateToString(node->getWhite(), node->getBlack())
                      << std::endl;
        }

        node->nextTurn();
    }
}
