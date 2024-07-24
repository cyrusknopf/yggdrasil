#include "mcts/gametree.h"

#include <cassert>
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
            // delete *it;
            children.erase(it);
            break;
        }
    }
    newOrphan->setParent(nullptr);
}

GameNode* GameNode::getParent() const { return parent; }

void GameNode::setParent(GameNode* newParent) { parent = newParent; }

std::vector<GameNode*>& GameNode::getChildren() { return children; }

void GameNode::setChildren(std::vector<GameNode*> newChildren) {
    children = newChildren;
}

GameNode* GameNode::getRandomChild(int seed) {
    std::vector<GameNode*> children = getChildren();

    std::mt19937 rng(seed);
    std::uniform_int_distribution<std::size_t> dist(0, children.size() - 1);
    std::size_t index = dist(rng);

    return children[index];
}

bitboard GameNode::getMove() const { return move; }

team GameNode::getWhite() const { return white; }

void GameNode::setWhite(team& boards) { white = boards; }

team GameNode::getBlack() const { return black; }

void GameNode::setBlack(team& boards) { black = boards; }

int GameNode::getVisits() { return visits; }

void GameNode::incrVisits() { visits++; }

int GameNode::getWins() const { return wins; }

void GameNode::incrWins() { wins++; }

bool GameNode::getTurn() const { return turn; }

void GameNode::nextTurn() { turn = !turn; }

double GameNode::evaluate(double constantOfInquisitiveness) {
    assert(parent != nullptr && "Evaluating node without parent");
    assert(parent->visits != 0 && "Parent never visited");
    assert(visits != 0 && "Node never visited");
    return ((double)wins / visits) +
           constantOfInquisitiveness * sqrt(log(parent->visits) / visits);
}

GameNode* initialiseTree(team& white, team& black) {
    return new GameNode(nullptr, 0, white, black, true);
}

GameNode* changeRoot(GameNode* oldRoot, GameNode* newRoot) {
    assert(oldRoot->getParent() == nullptr);
    std::vector<GameNode*> rootChildren = oldRoot->getChildren();
    assert(!rootChildren.empty());
    // Remove the child which is the new root
    for (auto it = rootChildren.begin(); it != rootChildren.end();) {
        if (*it == newRoot)
            it = rootChildren.erase(it);
        else
            ++it;
    }
    // All children (other than the new root - since it just got removed) are
    // then deleted in the call to the destructor
    oldRoot->setChildren(rootChildren);
    delete oldRoot;
    newRoot->setParent(nullptr);
    return newRoot;
}

GameNode* updateRootOnMove(bitboard move, GameNode* currentRoot) {
    assert(currentRoot->getParent() == nullptr);
    for (GameNode* child : currentRoot->getChildren()) {
        if (child->getMove() == move) {
            return changeRoot(currentRoot, child);
        }
    }
    assert(1 == 2 && "Child not found");
    return nullptr;
}

void GameNode::printGameNode(int indent) const {
    // Print indentation
    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }

    // Print node information
    std::cout << "Move: " << move << ", wins: " << wins
              << ", Visits: " << visits
              << ", Turn: " << (turn ? "White" : "Black") << std::endl;

    // std::cout << gameStateToString(white, black) << std::endl;

    // Recursively print children
    for (GameNode* child : children) {
        child->printGameNode(indent + 1);
    }
}

GameNode* getMostVisitedChild(GameNode* root) {
    int mostVisits = 0;
    GameNode* mostVisitedChild = nullptr;

    for (GameNode* child : root->getChildren()) {
        if (child->getVisits() > mostVisits) {
            mostVisits = child->getVisits();
            mostVisitedChild = child;
        }
    }

    assert(mostVisitedChild != nullptr);
    return mostVisitedChild;
}
