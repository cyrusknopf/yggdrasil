#include "mcts/gametree.h"

std::optional<bitboard> getRandomMove(GameNode* node, int pieceIndex);

std::pair<team, team> makeSimulatedMove(team& white, team& black, bitboard move,
                                        int index, bool turn);

int simulate(GameNode* node);
