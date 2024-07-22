#include "mcts/expansion.h"

#include <assert.h>

#include <utility>
#include <vector>

#include "game/moves.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "utils.h"

void expansion(GameNode* parent) {
    team white = parent->getWhite();
    team black = parent->getBlack();

    for (int i = 0; i < 6; i++) {
        std::vector<bitboard> moves =
            pseudoLegalFromIndex(i, white, black, parent->getTurn());

        for (auto& move : moves) {
            assert(move != 0);

            std::pair<team, team> newBoards =
                makeSimulatedMove(white, black, move, i, parent->getTurn());

            parent->addChild(parent, move, newBoards.first, newBoards.second);
        }
    }
}
