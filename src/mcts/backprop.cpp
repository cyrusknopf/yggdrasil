#include "mcts/backprop.h"

void backpropagate(GameNode* node, int value) {
    while (node->getParent() != nullptr) {
        node->getParent()->incrVisits();
        node->getParent()->alterScore(value);
        backpropagate(node->getParent(), value);
    }
}
