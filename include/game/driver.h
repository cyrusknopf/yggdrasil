#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <optional>

#include "utils.h"

/*
 * Given a single bitboard (possibly with multiple pieces), adds the provided
 * symbol to each location on the provided string board representation
 *
 * @param [board] string representation of the board
 * @param [pieceBitboard] bitboard to add to the string representation
 * @param [symbol] symbol to use as representation at each location
 * @return updated string representation of the board
 */
std::string addPieceToStringBoard(std::string& board, bitboard pieceBitboard,
                                  const std::string& symbol);

/*
 * Takes input from user via cin, expecting a coordinate on a chess board. If
 * the input is not a valid coordinate, returns a nullopt, otherwise, returns a
 * bitboard with a single 1 at the provided coordinate
 *
 * @return either bitboard of inputted coordinate or nullopt
 */
std::optional<bitboard> readSquare();

/*
 * Contains logic for accepting from and to locations for a move
 */
std::pair<bitboard, bitboard> takeToAndFrom(team& white, team& black,
                                            std::string& message);

void gameLoop();

#endif
