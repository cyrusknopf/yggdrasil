#include "utils.h"
#include <vector>

class GameNode {
    GameNode *parent;
    std::vector<GameNode *> children;
    team white;
    team black;
    bitboard move;
    double value;
    int visits;
    bool turn;

  public:
    GameNode(GameNode *parent, team *white, team *black, bitboard move,
             double value, bool turn)
        : parent(parent), children(std::vector<GameNode *>{}), white(*white),
          black(*black), move(move), visits(0), turn(turn){};

    ~GameNode(){};

    void addChild(GameNode *child);

    GameNode *getParent() const;
    const std::vector<GameNode *> &getChildren();

    void incrVisits();
};
