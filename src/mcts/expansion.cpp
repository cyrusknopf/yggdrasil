#include "mcts/expansion.h"

#include <assert.h>

#include <utility>
#include <vector>

#include "game/chess.h"
#include "game/moves.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "utils.h"

void expansion(GameNode* parent) {
    team white = parent->getWhite();
    team black = parent->getBlack();

    std::vector<std::pair<bitboard, int>> moves =
        getAllLegalMoves(white, black, parent->getTurn());

    for (auto& [move, pieceIndex] : moves) {
        assert(move != 0);

        auto [newWhite, newBlack] =
            makeMove(white, black, move, pieceIndex, parent->getTurn());

        GameNode* child = parent->addChild(parent, move, newWhite, newBlack);
        team childWhite = child->getWhite();
        team childBlack = child->getBlack();
        // TODO results in backprop the wrong value in driver
        if (getAllLegalMoves(childWhite, childBlack, child->getTurn())
                .empty()) {
            child->setTerminal();
            // Do not set winner, keep as nullopt to denote draw
        };
        // Black wins
        if (isMated(newWhite, newBlack, true)) {
            child->setTerminal();
            child->setWinner(false);
            // white wins
        } else if (isMated(newWhite, newBlack, false)) {
            child->setTerminal();
            child->setWinner(true);
        }
    }
}
