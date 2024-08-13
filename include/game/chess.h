#ifndef _CHESS_H_
#define _CHESS_H_

#include <utility>
#include <vector>

#include "utils.h"

/*
 * Initialises the two arrays for bitboards for each team and returns them as a
 * pair
 *
 * @return pair of bitboard arrays, first being white pieces, second being black
 * pieces
 */
std::pair<team, team> initGame();

/*
 * Given two team arrays (of the same colour), determines whether there has been
 * capture
 *
 * @param [oldBoards] team array before move
 * @param [newBoards] team array after move; where a possible capture may have
 * occured
 * @returns true if there has been a capture, false other if not
 */
bool checkIfCapture(team& oldBoards, team& newBoards);

/*
 * Given a team array, `t`, and specifier of what colour team, `colour`, (white
 * = true), returns a vector of <singleton bitboard, piece index> pairs where
 * each singleton bitboard contains the square a pawn is on to be promoted, and
 * four copies, each with one of piece index for: horse, castle, bishop, queen
 *
 * @param [t] team array to get promotable pawns for
 * @param [colour] specifier of the colour of the provided team array
 * @returns vector of <square, pieceIdx> pairs containing possible promotions
 */
std::vector<std::pair<bitboard, int>> getPromotions(team& t, bool colour);

/*
 * Given a promotion pair (from `getPromotions`), updates the provided team
 * arrays by applying that promotion to the team specified by `promoted` bool
 * (white = true). Returns the updated team arrays
 *
 * @param [promotion] <singletonBitboard,pieceIdx> specifying promotion to make
 * @param [white] white team array
 * @param [black] black team array
 * @param [promoted] colour of pawn to promote
 * @returns update team arrays [white, black] with promotion made
 */
std::pair<team, team> promotePawn(std::pair<bitboard, int> promotion,
                                  team& white, team& black, bool promoted);

/*
 * Checks whether the player of the specified `colour` is is mated
 *
 * @param [white] white team array
 * @param [black] black team array
 * @param [colour] player to check if mated: true = white
 * @returns true if player `colour` is in checkmate, false otheriwse
 */
bool isMated(team& white, team& black, bool colour);

/*
 * Checks whether either player has won
 * @param [white] white team array
 * @param [black] black team array
 * @returns true if white has won, false if black has won, nullopt if neither
 */
std::optional<bool> getWinner(team& white, team& black);

/*
 * Retuns a single bitboard with a 1 in each location which there is a piece.
 * Loss of information as to which piece is at each location
 *
 * @param [white] array of white bitboards
 * @param [black] array of black bitboards
 * @return bitboard of every piece on the board, from both teams
 */
bitboard getGameState(team& white, team& black);

/*
 * Returns a single bitboard with a 1 in each location where there is a piece
 * for the team specified by the colour parameter
 *
 * @param [white] array of white bitboards
 * @param [black] array of black bitboards
 * @param [colour] colour to return state of (white=true)
 * @return bitboard of every piece on the board, from specified team
 */
bitboard getGameState(team& white, team& black, bool colour);

/*
 * Returns a single bitboard with a 1 in each location where there is a piece in
 * provided team array
 *
 * @param [pieces] team array of bitboards to get state of
 * @return bitboard of every piece on the provided team
 */
bitboard getTeamState(team& pieces);

/*
 * Updates team boards white and black given a move, the index of the piece
 * making the move, and the turn of the moving piece (white = true)
 *
 * @param [white] team array of white pieces
 * @param [black] team array of black pieces
 * @param [move] bitboard containg the state of the piece after the move
 * @param [index] index in team array of the moving piece (1=pawn, ...,
 * 5=king)
 * @param [turn] turn of moving piece (white = true)
 * @returns pair containg the new team arrays: <white, black>
 */
std::pair<team, team> makeMove(team& white, team& black, bitboard move,
                               int index, bool turn);

#endif  // !_CHESS_H_
