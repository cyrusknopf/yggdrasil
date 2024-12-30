#include "mcts/expansion.h"

#include <assert.h>

#include <utility>
#include <vector>

#include "game/chess.h"
#include "game/moves.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "utils.h"

static void updateChildTerminal(GameNode* child) {
    team childWhite = child->getWhite();
    team childBlack = child->getBlack();
    bool turn = child->getTurn();

    // Given the new gamestate, if there are now no legal moves to be
    // made, the game is a stalemate
    if (getAllLegalMoves(childWhite, childBlack, turn).empty()) {
        child->setTerminal();
        // Do not set winner, keep as nullopt to denote draw
    };

    // If the player to move is mated: -> set terminal and winner to parent turn
    if (isMated(childWhite, childBlack, turn)) {
        child->setTerminal();
        child->setWinner(!turn);
    }
}

void expansion(GameNode* parent) {
    // Get the games state
    team white = parent->getWhite();
    team black = parent->getBlack();
    bool turn = parent->getTurn();

    // `parent`'s turn is the one to move next: get moves for that player
    std::vector<Move> moves = getAllLegalMoves(white, black, turn);

    for (auto& [move, pieceIndex] : moves) {
        assert(move != 0);

        auto [newWhite, newBlack] =
            makeMove(white, black, move, pieceIndex, parent->getTurn());

        // If moving piece is not a pawn(0): don't need to check promotions
        if (pieceIndex != 0) {
            GameNode* child = parent->addChild(move, newWhite, newBlack);
            updateChildTerminal(child);
        } else {  // If the moving piece IS a pawn, check promotions:
            team own = turn ? newWhite : newBlack;
            auto promotions = getPromotions(own, turn);
            // If no promotions to be made, add child as normal
            if (promotions.empty()) {
                GameNode* child = parent->addChild(move, newWhite, newBlack);
                updateChildTerminal(child);
            } else {  // If there are promotions: add each as a child
                for (auto& promote : promotions) {
                    // Get the new team arrays of each promotion
                    auto [pWhite, pBlack] =
                        promotePawn(promote, newWhite, newBlack, turn);
                    // Add them as a child
                    GameNode* child =
                        parent->addChild(promote.first, pWhite, pBlack);
                    // Update terminality
                    updateChildTerminal(child);
                }
            }
        }
    }
}
