#include "mcts/selection.h"

#include <float.h>

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

int findMinIndex(std::vector<double> scores) {
    double smallest = DBL_MAX;
    int smallestIdx = -1;
    for (int i = 0; i < scores.size(); i++) {
        if (scores[i] < smallest) {
            smallest = scores[i];
            smallestIdx = i;
        }
    }
    return smallestIdx;
}

GameNode* heursiticSelectLeaf(GameNode* node) {
    // Find a node whose has no children i.e. a leaf
    while (node->getChildren().size() != 0) {
        const std::vector<GameNode*>& children = node->getChildren();
        std::vector<double> evals(children.size());
        // O(n)
        std::transform(children.begin(), children.end(), evals.begin(),
                       [](GameNode* n) { return n->evaluate(1.414); });
        int bestChildIndex;
        // O(n)
        // if (node->getTurn())
        bestChildIndex = findMaxIndex(evals);
        // else
        // bestChildIndex = findMinIndex(evals);
        GameNode* bestChild = children[bestChildIndex];
        return heursiticSelectLeaf(bestChild);
    }

    return node;
}
