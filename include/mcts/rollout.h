#include <optional>

#include "mcts/gametree.h"

/*
 * Randomly plays moves until a winner, from the state specified by the
 * provided game node
 *
 * @param [node] gamenode to play from
 * @param [quiet] if false, prints board each move to stdout
 * @returns true = white win, false = black win, nullopt = draw
 */
std::optional<bool> simulate(GameNode* node, int seed);
