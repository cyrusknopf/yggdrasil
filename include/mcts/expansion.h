
#include "mcts/gametree.h"

/*
 * Given a node which has just been added as part of expansion: updates its
 * `terminal` and `winner` member attributes, if the game state represented by
 * the child's `white` and `black` team boards is terminal
 *
 * @param [child] node to update members for
 */
static void updateChildTerminal(GameNode* child);

/*
 * Adds children to the node passed as `parent`: one child for each legal move
 * at the game state of `parent`. In the case that a pawn can be promoted: adds
 * one child for each possible promotion
 *
 * Adds children in order:
 * pawn moves, -> promotions (if applicable): horse, castle, bishop, queen
 * horse, castle, bishop, queen, king
 *
 * @param [parent] node to add children to
 */
void expansion(GameNode* parent);
