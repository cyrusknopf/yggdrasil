#include "mcts/gametree.h"

/*
 * Given a node in the game tree, which has had a random playout done from it,
 * updates the path from that node to the root based on the outcome of the game.
 * All ancestors have their `vists` member incremented, while only the nodes who
 * represent a move made by the winner of the playout have their wins
 * incremented
 * @param [node] game node from which the playout occurs
 * @param [winner] winner at this node: true = white, false = black, nullopt =
 * stalemate
 */
void backpropagate(GameNode* node, std::optional<bool> winner);
