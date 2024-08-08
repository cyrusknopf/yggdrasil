#include "mcts/backprop.h"

void backpropagate(GameNode* node, std::optional<bool> winner) {
    node->incrVisits();
    if (winner.has_value())
        if (node->getTurn() == winner) node->incrWins();
    if (node->getParent() != nullptr)
        return backpropagate(node->getParent(), winner);
    return;
}
