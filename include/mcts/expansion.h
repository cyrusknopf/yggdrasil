#include "mcts/gametree.h"

/*
 * Creates child nodes for each pseudolegal move possible at that node
 *
 * @param [parent] node to create children from
 */
void expansion(GameNode* parent);
