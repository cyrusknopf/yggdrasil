#include "mcts/gametree.h"

#include <cassert>
#include <cmath>
#include <optional>
#include <vector>

#include "utils.h"

GameNode* GameNode::addChild(bitboard move, team& white, team& black) {
    // Turn of this node = ~parent turn
    GameNode* child = new GameNode(this, move, white, black, !this->getTurn());
    this->children.push_back(child);
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

void GameNode::setChildren(std::vector<GameNode*> newChildren) {
    children = newChildren;
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

bool GameNode::getTerminal() const { return terminal; }

void GameNode::setTerminal() { terminal = true; }

std::optional<bool> GameNode::getWinner() const { return winner; }

void GameNode::setWinner(bool victor) { winner = victor; }

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

/*
 * Cannot use single ORd bitboard of white and black because different
 * promotions are indistinguishable from eachother: cannot update correctly
 */
GameNode* updateRootOnMove(GameNode* currentRoot, team& white, team& black) {
    // Assume the node we are deleting is a root i.e. no parent
    assert(currentRoot->getParent() == nullptr);
    // Check each child for the one who has the new gamestate
    for (GameNode* child : currentRoot->getChildren()) {
        if (child->getWhite() == white && child->getBlack() == black) {
            return changeRoot(currentRoot, child);
        }
    }
    // Should never reach here as `expansion` should have always been called
    // TODO replace with generating a new child: we have all the information we
    // need
    assert(1 == 2 && "Child not found");
    return nullptr;
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
