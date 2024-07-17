#include "mcts/gametree.h"
#include <vector>

void GameNode::addChild(GameNode *child) { children.push_back(child); }

GameNode *GameNode::getParent() const { return parent; }
const std::vector<GameNode *> &GameNode::getChildren() { return children; }

void GameNode::incrVisits() { visits++; }
