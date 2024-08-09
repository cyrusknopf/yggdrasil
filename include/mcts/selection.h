#ifndef _SELECION_H_
#define _SELECION_H_

#include <vector>

#include "mcts/gametree.h"

/*
 * Gets a random leaf of the tree with `node` as the root
 *
 * @param [node] node to search for leaf from
 * @param [seed] integer seed for RNG
 * @returns pointer to selected leaf
 */
GameNode* selectRandomLeaf(GameNode* node, int seed);

/*
 * Finds the index of the highest value of the vector of doubles
 *
 * @param [scores] vector of doubles
 * @returns index of highest score in `scores`
 */
int findMaxIndex(std::vector<double> scores);

/*
 * Uses the `evaluate` member function of the `GameNode` class to traverse the
 * tree, finding the leaf with the highest value
 *
 * @param [node] root of tree to traverse
 * @returns pointer to "best" leaf
 */
GameNode* heursiticSelectLeaf(GameNode* node);

#endif  // !_SELECION_H_
