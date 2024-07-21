#ifndef _SELECION_H_
#define _SELECION_H_

#include <vector>

#include "mcts/gametree.h"

GameNode* selectRandomLeaf(GameNode* node, int seed);

int findMaxIndex(std::vector<double> scores);

int findMinIndex(std::vector<double> scores);

GameNode* heursiticSelectLeaf(GameNode* node);
#endif  // !_SELECION_H_
