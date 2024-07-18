#ifndef _GAMETREE_H_
#define _GAMETREE_H_

#include <vector>

#include "utils.h"

class GameNode {
    GameNode* parent;
    std::vector<GameNode*> children;
    bitboard move;
    team* white;
    team* black;
    double value;
    int visits;
    bool turn;

   public:
    GameNode(GameNode* parent, bitboard move, team* white, team* black,
             double value, bool turn)
        : parent(parent),
          children(std::vector<GameNode*>{}),
          move(move),
          white(white),
          black(black),
          value(value),
          visits(0),
          turn(turn){};

    ~GameNode(){};

    void addChild(GameNode* child);

    GameNode* getParent() const;

    const std::vector<GameNode*>& getChildren();

    const GameNode getRandomChild(int seed);

    const double getValue();

    void incrVisits();
};

GameNode initialiseAgent(team& white, team& black);

#endif  // !_GAMETREE_H_
