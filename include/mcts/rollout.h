#include "mcts/gametree.h"

std::optional<bitboard> getRandomMove(GameNode* node, int pieceIndex);

std::pair<team, team> makeMove(team white, team black, bitboard move, int index,
                               bool turn);

int simulate(GameNode* node);
