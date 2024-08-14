#include "mcts/selection.h"

#include <float.h>

#include <cassert>
#include <cfloat>

#include "mcts/gametree.h"

GameNode* selectRandomLeaf(GameNode* node, int seed) {
    const std::vector<GameNode*>& children = node->getChildren();

    // Find a node whose has no children i.e. a leaf
    while (children.size() != 0) {
        GameNode* randomChild = getRandom(node->getChildren() ,seed);
        return selectRandomLeaf(randomChild, seed);
    }
    return node;
}

int findMaxIndex(std::vector<double> scores) {
    double largest = -DBL_MAX;
    int largestIdx = -1;
    for (int i = 0; i < scores.size(); i++) {
        if (scores[i] > largest) {
            largest = scores[i];
            largestIdx = i;
        }
    }
    return largestIdx;
}

GameNode* heursiticSelectLeaf(GameNode* node) {
    // Find a node whose has no children i.e. a leaf
    while (node->getChildren().size() != 0) {
        const std::vector<GameNode*>& children = node->getChildren();
        std::vector<double> evals(children.size());
        // O(n)
        std::transform(children.begin(), children.end(), evals.begin(),
                       [](GameNode* n) { return n->evaluate(1.141); });
        int bestChildIndex;
        // O(n)
        bestChildIndex = findMaxIndex(evals);
        assert(bestChildIndex != -1);
        GameNode* bestChild = children.at(bestChildIndex);
        return heursiticSelectLeaf(bestChild);
    }
    return node;
}
