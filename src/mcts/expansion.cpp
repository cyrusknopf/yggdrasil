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
    // Get the games state
    team white = parent->getWhite();
    team black = parent->getBlack();

    // `parent`'s turn is the one to move next: get moves for that player
    std::vector<std::pair<bitboard, int>> moves =
        getAllLegalMoves(white, black, parent->getTurn());

    for (auto& [move, pieceIndex] : moves) {
        assert(move != 0);

        auto [newWhite, newBlack] =
            makeMove(white, black, move, pieceIndex, parent->getTurn());

        // TODO check promotes empty here:yes->add one else add one per promote
        GameNode* child = parent->addChild(move, newWhite, newBlack);
        team childWhite = child->getWhite();
        team childBlack = child->getBlack();

        // Given the new gamestate, if there are now no legal moves to be made,
        // the game is a stalemate
        if (getAllLegalMoves(childWhite, childBlack, child->getTurn())
                .empty()) {
            child->setTerminal();
            // Do not set winner, keep as nullopt to denote draw
        };

        // Given the new gamestate, if either player is mated, set the node to
        // be terminal and set the winner of the node
        // TODO only need to check one here: i.e. white can never be mated if
        // white just moved
        if (isMated(newWhite, newBlack, true)) {
            child->setTerminal();
            child->setWinner(false);
            // White wins
        } else if (isMated(newWhite, newBlack, false)) {
            child->setTerminal();
            child->setWinner(true);
        }
    }
}
