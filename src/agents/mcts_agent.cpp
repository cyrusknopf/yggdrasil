#include "agents/mcts_agent.h"

#include <iostream>

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
        // Select node to random simul from
        GameNode* L = heursiticSelectLeaf(root);
        // If the selected node is terminal, just backprop the outcome...
        if (L->getTerminal()) {
            backpropagate(L, !L->getWinner());
            // ... and chose a new node
            continue;
        }
        // ... otherwise add the child moves
        expansion(L);
        // Chose a random move
        GameNode* C = getRandom(L->getChildren(), seed);
        // Next iter if the node is terminal
        if (C->getTerminal()) {
            backpropagate(C, !C->getWinner());
            continue;
        }
        std::optional<bool> res = simulate(C, seed);
        gamesSimulated++;
        backpropagate(C, !res);
    }
    GameNode* newState = getMostVisitedChild(root);

    whiteBitboards = newState->getWhite();
    blackBitboards = newState->getBlack();
    root = updateRootOnMove(root, whiteBitboards, blackBitboards);

    return root;
}
