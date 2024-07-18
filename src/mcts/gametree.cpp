#include "mcts/gametree.h"

#include <random>
#include <vector>

void GameNode::addChild(GameNode* child) { children.push_back(child); }

GameNode* GameNode::getParent() const { return parent; }

const std::vector<GameNode*>& GameNode::getChildren() { return children; }

const GameNode GameNode::getRandomChild(int seed) {
    std::vector<GameNode*> children = getChildren();

    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::size_t> dist(0, children.size() - 1);
    std::size_t index = dist(rng);

    return *children[index];
}

const double GameNode::getValue() { return value; }

void GameNode::incrVisits() { visits++; }

GameNode initialiseAgent(team& white, team& black) {
    GameNode root = GameNode(nullptr, 0, &white, &black, 0, true);
    return root;
}
