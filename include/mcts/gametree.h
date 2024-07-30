#ifndef _GAMETREE_H_
#define _GAMETREE_H_

#include <vector>

#include "utils.h"

class GameNode {
    // Pointer to parent of this node
    GameNode* parent;
    // Vec of pointers to the children of this node
    std::vector<GameNode*> children;
    // The move in the game which this node represents
    bitboard move;
    // Team array of white after the move is made
    team white;
    // Team array of black after the move is made
    team black;
    // Number of wins of games played from this node
    int wins;
    // Number of games played from this node
    int visits;
    // Turn of player at this node (true = white)
    bool turn;

   public:
    GameNode(GameNode* parent, bitboard move, team& white, team& black,
             bool turn)
        : parent(parent),
          children(),
          move(move),
          white(white),
          black(black),
          wins(0),
          visits(1),
          turn(turn){};

    // Deletes all children. `changeRoot` should be called to update root of
    // game tree
    ~GameNode() {
        if (children.size() != 0) {
            for (GameNode* child : children) {
                delete child;
            }
            children.clear();
        }
    };

    GameNode* addChild(GameNode* parent, bitboard move, team& white,
                       team& black);

    void removeChild(GameNode* newOrphan);

    GameNode* getParent() const;

    void setParent(GameNode* newParent);

    std::vector<GameNode*>& getChildren();

    void setChildren(std::vector<GameNode*> newChildren);

    GameNode* getRandomChild(int seed);

    bitboard getMove() const;

    team getWhite() const;

    void setWhite(team& boards);

    team getBlack() const;

    void setBlack(team& boards);

    int getVisits();

    void incrVisits();

    int getWins() const;

    void incrWins();

    bool getTurn() const;

    void nextTurn();

    double evaluate(double constantofInquisitiveness);

    void printGameNode(int indent = 0) const;
};

GameNode* changeRoot(GameNode* oldRoot, GameNode* newRoot);

GameNode* updateRootOnMove(bitboard move, GameNode* currentRoot);

GameNode* initialiseTree(team& white, team& black);

GameNode* getMostVisitedChild(GameNode* root);

#endif  // !_GAMETREE_H_
