#include "mcts/rollout.h"

#include <assert.h>

#include <iostream>
#include <optional>
#include <utility>
#include <vector>

#include "game/chess.h"
#include "game/moves.h"
#include "utils.h"

std::optional<bool> simulate(GameNode* node, bool quiet) {
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
            return winner;
        }
        // White wins
        if (isMated(white, black, false)) {
            bool winner = true;
            return winner;
        }

        std::vector<std::pair<bitboard, int>> legalMoves =
            getAllLegalMoves(white, black, turn);
        // No legals: stalemate
        if (legalMoves.empty()) {
            return std::nullopt;
        }

        std::random_device rd;
        auto [randomMove, pieceIdx] = getRandom(legalMoves, (int)rd());

        auto [newWhite, newBlack] =
            makeMove(white, black, randomMove, pieceIdx, turn);

        // Check if need promote
        team own = turn ? newWhite : newBlack;
        std::vector<std::pair<bitboard, int>> promotes =
            getPromotions(own, turn);

        // If there is a promote to make, make a random one
        if (!promotes.empty()) {
            std::pair<bitboard, int> rdmPromote =
                getRandom(promotes, (int)rd());
            std::pair<team, team> newBoards =
                promotePawn(rdmPromote, newWhite, newBlack, turn);
            newWhite = newBoards.first;
            newBlack = newBoards.second;
        }

        // If there is no capture, increment half move clock
        if (turn) {
            if (!checkIfCapture(black, newBlack))
                halfMoveClock++;
            else
                halfMoveClock = 0;
        } else {
            if (!checkIfCapture(white, newWhite))
                halfMoveClock++;
            else
                halfMoveClock = 0;
        }

        // Stalemate
        if (halfMoveClock >= 100) {
            return std::nullopt;
        }

        white = newWhite;
        black = newBlack;

        turn = !turn;
    }
}
