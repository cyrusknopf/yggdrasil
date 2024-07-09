#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "utils.h"

bitboard coordinateToState(const std::string &coord);

std::string addPieceToStringBoard(std::string &board, bitboard pieceBitboard,
                                  const std::string &symbol);

std::string gameStateToString(std::array<bitboard, 6> &whitePieces,
                              std::array<bitboard, 6> &blackPieces);

std::string readSquare(std::array<bitboard, 6> &whitePieces,
                       std::array<bitboard, 6> &blackPieces);

std::pair<std::array<bitboard, 6>, std::array<bitboard, 6>>
readMove(std::array<bitboard, 6> &whitePieces,
         std::array<bitboard, 6> &blackPieces, bool turn);

void gameLoop();

#endif
