#include "utils.h"

void gameLoop();

std::string readSquare();

void printGameState(std::array<bitboard, 6> &whitePieces,
                    std::array<bitboard, 6> &blackPieces);

bitboard coordinateToState(std::string coord);
