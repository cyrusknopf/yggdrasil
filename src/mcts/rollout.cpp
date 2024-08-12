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

        auto [randomMove, pieceIdx] = getRandomLegalMove(legalMoves);

        auto [newWhite, newBlack] =
            makeMove(white, black, randomMove, pieceIdx, turn);

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
