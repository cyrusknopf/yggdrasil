#include "mcts/expansion.h"

#include <__iterator/bounded_iter.h>

#include <iostream>
#include <utility>
#include <vector>

#include "game/driver.h"
#include "game/moves.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "utils.h"

GameNode* expansion(GameNode* parent) {
    team white = parent->getWhite();
    team black = parent->getBlack();

    for (int i = 0; i < 6; i++) {
        std::vector<bitboard> moves =
            pseudoLegalFromIndex(i, white, black, parent->getTurn());

        for (auto& move : moves) {
            std::pair<team, team> newBoards =
                makeSimulatedMove(white, black, move, i, parent->getTurn());

            std::cout << "in expansion" << std::endl;
            std::cout << gameStateToString(newBoards.first, newBoards.second);

            GameNode* thisChild =
                new GameNode(parent, move, newBoards.first, newBoards.second,
                             !parent->getTurn());

            std::cout << "child in func" << std::endl;
            std::cout << gameStateToString(thisChild->getWhite(),
                                           thisChild->getBlack());

            return thisChild;
        }
    }
    return nullptr;
}
