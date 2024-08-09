#include "mcts/backprop.h"

void backpropagate(GameNode* node, std::optional<bool> winner) {
    // Increment visits regardless of outcome
    node->incrVisits();
    // If not a stalemate, we need to update `wins` member
    if (winner.has_value())
        // XXX should be reversed
        if (node->getTurn() == winner) node->incrWins();
    // If this node is not the root, we must update ancestors
    if (node->getParent() != nullptr)
        return backpropagate(node->getParent(), winner);
    return;
}
