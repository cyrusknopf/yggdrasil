#include "utils.h"
#include <utility>

/*
 * Initialises the two arrays for bitboards for each team and returns them as a
 * pair
 *
 * @return pair of bitboard arrays, first being white pieces, second being black
 * pieces
 */
std::pair<team, team> initGame();

/*
 * Retuns a single bitboard with a 1 in each location which there is a piece.
 * Loss of information as to which piece is at each location
 *
 * @param [white] array of white bitboards
 * @param [black] array of black bitboards
 * @return bitboard of every piece on the board, from both teams
 */
bitboard getGameState(team &white, team &black);

/*
 * Returns a single bitboard with a 1 in each location where there is a piece
 * for the team specified by the colour parameter
 *
 * @param [white] array of white bitboards
 * @param [black] array of black bitboards
 * @param [colour] colour to return state of (white=true)
 * @return bitboard of every piece on the board, from specified team
 */
bitboard getGameState(team &white, team &black, bool colour);

/*
 * Returns a single bitboard with a 1 in each location where there is a piece in
 * provided team array
 *
 * @param [pieces] team array of bitboards to get state of
 * @return bitboard of every piece on the provided team
 */
bitboard getTeamState(team &pieces);
