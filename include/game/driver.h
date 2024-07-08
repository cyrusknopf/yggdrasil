#include "utils.h"

bitboard coordinateToState(std::string &coord);

std::string addPieceToStringBoard(std::string &board, bitboard pieceBitboard,
                                  const std::string &symbol);

void printGameState(std::array<bitboard, 6> &whitePieces,
                    std::array<bitboard, 6> &blackPieces);

std::string readSquare(std::array<bitboard, 6> &whitePieces,
                       std::array<bitboard, 6> &blackPieces);

void readMove(std::array<bitboard, 6> &whitePieces,
              std::array<bitboard, 6> &blackPieces, bool turn);

void gameLoop();
