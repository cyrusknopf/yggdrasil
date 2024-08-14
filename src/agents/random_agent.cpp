#include "agents/random_agent.h"

#include <random>
#include <utility>
#include <vector>

#include "game/chess.h"
#include "game/moves.h"
#include "utils.h"

std::pair<team, team> RandomAgent::takeTurn(team whiteBitboards,
                                            team blackBitboards, bool turn) {
    std::random_device rd;
    std::vector<std::pair<bitboard, int>> moves =
        getAllLegalMoves(whiteBitboards, blackBitboards, turn);

    auto [randomMove, randomMoveIdx] = getRandom(moves, (int)rd());

    auto [newWhite, newBlack] = makeMove(whiteBitboards, blackBitboards,
                                         randomMove, randomMoveIdx, turn);

    team own = turn ? newWhite : newBlack;
    std::vector<std::pair<bitboard, int>> promotes = getPromotions(own, turn);
    if (promotes.empty()) return std::make_pair(newWhite, newBlack);

    std::pair<bitboard, int> rdmPromote = getRandom(promotes, (int)rd());
    auto pBoards = promotePawn(rdmPromote, newWhite, newBlack, turn);
    return pBoards;
}
