#include "mcts/backprop.h"

void backpropagate(GameNode* node, std::optional<bool> winner) {
    while (node->getParent() != nullptr) {
        node->getParent()->incrVisits();
        // Only increment wins if there was a winner
        if (winner.has_value()) {
            if (node->getParent()->getTurn() == winner)
                node->getParent()->incrWins();
        }
        return backpropagate(node->getParent(), winner);
    }
    return;
}
