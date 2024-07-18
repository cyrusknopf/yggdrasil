#include "mcts/selection.h"

GameNode selectChild(GameNode& node) {
    // Find a node whose has no children i.e. a leaf
    const std::vector<GameNode*>& children = node.getChildren();

    while (children.size() != 0) {
        GameNode randomChild = node.getRandomChild(rand());
        return selectChild(randomChild);
    }
    return node;
}
