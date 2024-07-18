#include "mcts/selection.h"

GameNode selectRandomLeaf(GameNode& node, int seed) {
    // Find a node whose has no children i.e. a leaf
    const std::vector<GameNode*>& children = node.getChildren();

    while (children.size() != 0) {
        GameNode randomChild = node.getRandomChild(seed);
        return selectRandomLeaf(randomChild, seed);
    }
    return node;
}
