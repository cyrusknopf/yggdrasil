#ifndef _GAMETREE_H_
#define _GAMETREE_H_

#include <vector>

#include "utils.h"

class GameNode {
    GameNode* parent;
    std::vector<GameNode*> children;
    bitboard move;
    team white;
    team black;
    int wins;
    int visits;
    bool turn;
    bool terminal;

   public:
    GameNode(GameNode* parent, bitboard move, team& white, team& black,
             bool turn)
        : parent(parent),
          children(),
          // children(std::vector<GameNode*>{}),
          move(move),
          white(white),
          black(black),
          wins(0),
          visits(1),
          turn(turn),
          terminal(false){};

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

    bool getTerminal() const;

    void setTerminal();

    double evaluate(double constantofInquisitiveness);

    void printGameNode(int indent = 0) const;
};

GameNode* changeRoot(GameNode* oldRoot, GameNode* newRoot);

GameNode* updateRootOnMove(bitboard move, GameNode* currentRoot);

GameNode* initialiseTree(team& white, team& black);

GameNode* getMostVisitedChild(GameNode* root);

#endif  // !_GAMETREE_H_
