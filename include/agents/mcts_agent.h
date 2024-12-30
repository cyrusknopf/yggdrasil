#ifndef _MCTS_AGENT_H_
#define _MCTS_AGENT_H_

#include "mcts/gametree.h"

class MCTSAgent {
    int moveTime;
    int seed;

   public:
    MCTSAgent(int thisMoveTime, int thisSeed) {
        moveTime = thisMoveTime;
        seed = thisSeed;
    }

    GameNode* takeTurn(GameNode* root, team whiteBitboards, team blackBitboards,
                       bool quiet);
};
#endif  // !__MCTS_H_
