#include "mcts/gametree.h"
#include <vector>

GameNode *selectChild(GameNode *root) {
    // Find a node whose has no children i.e. a leaf
    const std::vector<GameNode *> &children = root->getChildren();
    while (children.size() != 0) {
    }
}
