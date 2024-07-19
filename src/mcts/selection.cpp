#include "mcts/selection.h"

#include <algorithm>

#include "mcts/gametree.h"

GameNode* selectRandomLeaf(GameNode* node, int seed) {
    const std::vector<GameNode*>& children = node->getChildren();

    // Find a node whose has no children i.e. a leaf
    while (children.size() != 0) {
        GameNode* randomChild = node->getRandomChild(seed);
        return selectRandomLeaf(randomChild, seed);
    }
    return node;
}

GameNode* heursiticSelectLeaf(GameNode* node, int seed) {
    const std::vector<GameNode*>& children = node->getChildren();

    // Find a node whose has no children i.e. a leaf
    while (children.size() != 0) {
        std::vector<double> evals(children.size());
        std::transform(children.begin(), children.end(), evals.begin(),
                       [](GameNode* n) { return n->evaluate(1.414); });
    }

    return node;
}
