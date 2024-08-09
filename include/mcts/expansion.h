
#include "mcts/gametree.h"

/*
 * Adds children to the node passed as `parent`: one child for each legal move
 * at the game state of `parent`.
 *
 * @param [parent] node to add children to
 */
void expansion(GameNode* parent);
