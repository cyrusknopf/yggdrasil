#include "agents/random_agent.h"

#include "game/chess.h"
#include "mcts/rollout.h"

std::pair<team, team> RandomAgent::takeTurn(team whiteBitboards,
                                            team blackBitboards, bool turn) {
    std::vector<std::pair<bitboard, int>> moves =
        getAllLegalMoves(whiteBitboards, blackBitboards, turn);

    auto [randomMove, randomMoveIdx] = getRandomLegalMove(moves, turn);

    auto [newWhite, newBlack] = makeMove(whiteBitboards, blackBitboards,
                                         randomMove, randomMoveIdx, turn);

    return std::make_pair(newWhite, newBlack);
}