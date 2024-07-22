#include "mcts/gametree.h"

#include <assert.h>

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "utils.h"

GameNode* GameNode::addChild(GameNode* parent, bitboard move, team& white,
                             team& black) {
    GameNode* child =
        new GameNode(parent, move, white, black, !parent->getTurn());
    parent->children.push_back(child);
    return child;
}

void GameNode::removeChild(GameNode* newOrphan) {
    for (auto it = children.begin(); it != children.end(); it++) {
        if (*it == newOrphan) {
            children.erase(it);
            break;
        }
    }
    newOrphan->setParent(nullptr);
}

GameNode* GameNode::getParent() const { return parent; }

void GameNode::setParent(GameNode* newParent) { parent = newParent; }

std::vector<GameNode*>& GameNode::getChildren() { return children; }

GameNode* GameNode::getRandomChild(int seed) {
    std::vector<GameNode*> children = getChildren();

    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::size_t> dist(0, children.size() - 1);
    std::size_t index = dist(rng);

    return children[index];
}

team GameNode::getWhite() const { return white; }

void GameNode::setWhite(team& boards) { white = boards; }

team GameNode::getBlack() const { return black; }

void GameNode::setBlack(team& boards) { black = boards; }

void GameNode::incrVisits() { visits++; }

int GameNode::getScore() const { return score; }

void GameNode::alterScore(int amnt) { score += amnt; }

bool GameNode::getTurn() const { return turn; }

void GameNode::nextTurn() { turn = !turn; }

double GameNode::evaluate(double constantOfInquisitiveness) {
    assert(parent != nullptr && "Evaluating node without parent");
    assert(parent->visits != 0 && "Parent never visited");
    assert(visits != 0 && "Node never visited");
    return ((double)score / visits) +
           constantOfInquisitiveness * sqrt(log(parent->visits) / visits);
}

GameNode* initialiseTree(team& white, team& black) {
    return new GameNode(nullptr, 0, white, black, true);
}

GameNode* changeRoot(GameNode* oldRoot, GameNode* newRoot) {
    assert(oldRoot->getParent() == nullptr);
    std::vector<GameNode*> rootChildren = oldRoot->getChildren();
    assert(rootChildren.size() != 0);
    // Delete all children that are not the new root
    for (auto child : rootChildren) {
        if (child != newRoot) {
            delete child;
        }
    }
    delete oldRoot;
    newRoot->setParent(nullptr);
    return newRoot;
}

void GameNode::printGameNode(int indent) const {
    // Print indentation
    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }

    // Print node information
    std::cout << "Move: " << move << ", Score: " << score
              << ", Visits: " << visits
              << ", Turn: " << (turn ? "White" : "Black") << std::endl;

    std::cout << gameStateToString(white, black) << std::endl;

    // Recursively print children
    for (GameNode* child : children) {
        child->printGameNode(indent + 1);
    }
}
