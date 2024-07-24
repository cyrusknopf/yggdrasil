#include "mcts/backprop.h"

void backpropagate(GameNode* node, bool winner) {
    while (node->getParent() != nullptr) {
        node->getParent()->incrVisits();
        if (node->getParent()->getTurn() == winner)
            node->getParent()->incrWins();
        return backpropagate(node->getParent(), winner);
    }
    return;
}
