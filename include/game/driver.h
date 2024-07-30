#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <optional>

#include "utils.h"

/*
 * Takes input from user via cin, expecting a coordinate on a chess board. If
 * the input is not a valid coordinate, returns a nullopt, otherwise, returns a
 * bitboard with a single 1 at the provided coordinate
 *
 * @return either bitboard of inputted coordinate or nullopt
 */
std::optional<bitboard> readSquare();

/*
 * Loops until two valid chess square coordinates have been entered via
 * `readSquare`. Prints the chess board state to stdout. Contains a message
 * which can give user feedback such as invalid move, etc
 *
 * @param [white] white team array of bitboards
 * @param [black] black team array of bitboards
 * @param [message] message to display under chess board in stdout
 * @returns pair containing single 1 bitboards of the to and from squares
 */
std::pair<bitboard, bitboard> takeToAndFrom(team& white, team& black,
                                            std::string& message);

/*
 * Loops until a valid move has been taken from `takeToAndFrom`.
 * Checks that there is a piece at the 'from square' and that the 'to square' is
 * a valid move for that piece. Retruns a tuple of information about the move.
 *
 * @param [white] white team array of bitboards
 * @param [black] black team array of bitboards
 * @param [turn] turn of player (white = true)
 * @param [message] message to display under chess board in stdout
 * @returns tuple containing: <piece board after move, index of piece, singleton
 * bitboard of 'to square'>
 *
 */
std::tuple<bitboard, int, bitboard> takeMove(team& whiteBitboards,
                                             team& blackBitboards, bool turn,
                                             std::string& message);

/*
 * Updates the two team arrays with the move information provided. Checks
 * whether the move involves a capture, and appropriately updates boards
 *
 * @param [whiteBitboards] white team array of bitboards
 * @param [blackBitboards] black team array of bitboards
 * @param [toSquare] singleton bitboard of move destination square
 * @param [newBoard] piece board post-move
 * @param [fromIdx] index of moving piece board in team array
 * @param [turn] turn of moving player (white = true)
 * @returns pair of team arrays, <white,black> with updated boards
 */
std::pair<team, team> makeMove(team& whiteBitboards, team& blackBitboards,
                               bitboard toSquare, bitboard newBoard,
                               int fromIdx, bool turn);
/*
 * Given a single bitboard (possibly with multiple pieces), adds the
 * provided symbol to each location on the provided string board
 * representation
 *
 * @param [board] string representation of the board
 * @param [pieceBitboard] bitboard to add to the string representation
 * @param [symbol] symbol to use as representation at each location
 * @return updated string representation of the board
 */
std::string addPieceToStringBoard(std::string& board, bitboard pieceBitboard,
                                  const std::string& symbol);

/*
 * Contains logic for running a game
 */
void gameLoop();

#endif
