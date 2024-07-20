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
    std::vector<bitboard> moves = pseudoLegalFromIndex(
        pieceIndex, node->getWhite(), node->getBlack(), node->getTurn());
    std::mt19937 rng(rand());
    std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
    std::size_t randomMoveIndex = dist(rng);

    if (moves.size() == 0) {
        return std::nullopt;
    }

    return moves[randomMoveIndex];
}

std::pair<team, team> makeMove(team white, team black, bitboard move, int index,
                               bool turn) {
    if (turn)
        white[index] = move;
    else
        black[index] = move;

    return std::make_pair(white, black);
}

int simulate(GameNode* node) {
    bool gameOver = false;
    while (!gameOver) {
        std::optional<bitboard> randomMove = std::nullopt;
        int randomPieceIndex;
        while (!randomMove.has_value()) {
            randomPieceIndex = rand() % 6;
            randomMove = getRandomMove(node, randomPieceIndex);
        }
        std::pair<team, team> newBoards =
            makeMove(node->getWhite(), node->getBlack(), randomMove.value(),
                     randomPieceIndex, node->getTurn());

        // Black wins
        if (newBoards.first[5] == 0) return -1;
        // White wins
        if (newBoards.second[5] == 0) return 1;

        node->setWhite(newBoards.first);
        node->setBlack(newBoards.second);

        std::cout << gameStateToString(node->getWhite(), node->getBlack())
                  << std::endl;

        node->nextTurn();
    }
}
