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
    int score;
    int visits;
    bool turn;

   public:
    GameNode(GameNode* parent, bitboard move, team& white, team& black,
             bool turn)
        : parent(parent),
          children(),
          // children(std::vector<GameNode*>{}),
          move(move),
          white(white),
          black(black),
          score(0),
          visits(1),
          turn(turn){};

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

    GameNode* getRandomChild(int seed);

    bitboard getMove() const;

    team getWhite() const;

    void setWhite(team& boards);

    team getBlack() const;

    void setBlack(team& boards);

    void incrVisits();

    int getScore() const;

    void alterScore(int amnt);

    bool getTurn() const;

    void nextTurn();

    double evaluate(double constantofInquisitiveness);

    void printGameNode(int indent = 0) const;
};

GameNode* changeRoot(GameNode* oldRoot, GameNode* newRoot);

GameNode* updateRootOnMove(bitboard move, GameNode* currentRoot);

GameNode* initialiseTree(team& white, team& black);

#endif  // !_GAMETREE_H_
