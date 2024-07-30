#include "mcts/gametree.h"

/*
 * Given a terminal node in the game tree, updates the values of nodes above
 * based on the winner, i.e. nodes whose turn = winner have their wins
 * incremented
 * @param [node] terminal game node
 * @param [winner] winner at this node
 */
void backpropagate(GameNode* node, std::optional<bool> winner);
