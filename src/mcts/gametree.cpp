#include "mcts/gametree.h"

#include <assert.h>

#include <cmath>
#include <random>
#include <vector>

#include "utils.h"

void GameNode::addChild(GameNode* child) { children.push_back(child); }

GameNode* GameNode::getParent() const { return parent; }

std::vector<GameNode*>& GameNode::getChildren() { return children; }

GameNode* GameNode::getRandomChild(int seed) {
    std::vector<GameNode*> children = getChildren();

    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::size_t> dist(0, children.size() - 1);
    std::size_t index = dist(rng);

    return children[index];
}

team& GameNode::getWhite() const { return white; }

void GameNode::setWhite(team& boards) { white = boards; }

team& GameNode::getBlack() const { return black; }

void GameNode::setBlack(team& boards) { black = boards; }

void GameNode::incrVisits() { visits++; }

void GameNode::incrWins() { wins++; }

bool GameNode::getTurn() const { return turn; }

void GameNode::nextTurn() { turn = !turn; }

double GameNode::evaluate(double constantOfInquisitiveness) {
    assert(parent != nullptr && "Evaluating node without parent");
    assert(parent->visits != 0 && "Parent never visited");
    if (visits == 0) incrVisits();
    return ((double)wins / visits) +
           constantOfInquisitiveness * sqrt(log(parent->visits) / visits);
}

GameNode initialiseTree(team& white, team& black) {
    GameNode root = GameNode(nullptr, 0, white, black, true);
    return root;
}
