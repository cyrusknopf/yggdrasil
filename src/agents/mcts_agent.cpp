#include "agents/mcts_agent.h"

#include <iostream>
#include <random>

#include "game/chess.h"
#include "mcts/backprop.h"
#include "mcts/expansion.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "mcts/selection.h"
#include "utils.h"

GameNode* MCTSAgent::takeTurn(GameNode* root, team whiteBitboards,
                              team blackBitboards, bool quiet) {
    int gamesSimulated = 0;
    std::cout << "Agent thinking..." << std::endl;
    root = updateRootOnMove(root, whiteBitboards, blackBitboards);

    time_t startTime = time(nullptr);
    while (time(nullptr) < startTime + moveTime) {
        if (!quiet) {
            std::cout << "\rSimulated games played: " << gamesSimulated
                      << std::flush;
        }
        GameNode* L = heursiticSelectLeaf(root);
        if (L->getTerminal()) {
            backpropagate(L, !L->getWinner());
            continue;
        }
        expansion(L);
        std::random_device rd;
        GameNode* C = L->getRandomChild(rd());
        // Next iter if the node is terminal
        if (C->getTerminal()) {
            continue;
        }
        std::optional<bool> res = simulate(C, true);
        gamesSimulated++;
        backpropagate(C, !res);
    }
    GameNode* newState = getMostVisitedChild(root);

    whiteBitboards = newState->getWhite();
    blackBitboards = newState->getBlack();
    root = updateRootOnMove(root, whiteBitboards, blackBitboards);

    return root;
}
