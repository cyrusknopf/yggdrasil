#include "mcts/gametree.h"

/*
 * Given a node of the game tree with a certain state, generates a random move
 * for the piece at provided index
 */
std::optional<bitboard> getRandomMove(GameNode* node, int pieceIndex);

std::pair<team, team> makeSimulatedMove(team& white, team& black, bitboard move,
                                        int index, bool turn);

int simulate(GameNode* node, bool quiet);
