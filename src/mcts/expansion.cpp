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

    std::vector<std::pair<bitboard, int>> moves =
        getAllLegalMoves(white, black, parent->getTurn());

    for (auto& [move, pieceIndex] : moves) {
        assert(move != 0);

        std::pair<team, team> newBoards =
            makeMove(white, black, move, pieceIndex, parent->getTurn());

        parent->addChild(parent, move, newBoards.first, newBoards.second);
    }
}
