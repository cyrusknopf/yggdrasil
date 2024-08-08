#ifndef __MCTS_AGENT_H_
#define __MCTS_AGENT_H_

#include "mcts/gametree.h"

class MCTSAgent {
    int moveTime;

   public:
    MCTSAgent(int thisMoveTime) { moveTime = thisMoveTime; }

    GameNode* takeTurn(GameNode* root, team whiteBitboards, team blackBitboards,
                       bool quiet);
};
#endif  // !__MCTS_H_
