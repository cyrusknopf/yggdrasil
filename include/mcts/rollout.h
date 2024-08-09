#include <optional>
#include <utility>

#include "mcts/gametree.h"
#include "utils.h"

/*
 * Provided a vector of [move, pieceindex] pairs, selects a random one and
 * returns that pair
 * Provided moves should be legal
 * @param [moves] vector of [move, pieceindex], output of `getAllLegalMoves`
 * @returns [move, pieceindex] pair
 */
std::pair<bitboard, int> getRandomLegalMove(
    std::vector<std::pair<bitboard, int>> moves);

/*
 * Given two team arrays, gets all the legal moves, for all pieces, for the
 * player specified by `colour`;
 *
 * @param [white] white team array
 * @param [black] black team array
 * @param [colour] player to find legal moves for: white = true
 */
std::vector<std::pair<bitboard, int>> getAllLegalMoves(team& white, team& black,
                                                       bool colour);
/*
 * DEPRECIATED
 * Given both team arrays ,generates a random move
 * for the piece at provided index. Index should be a random number between
 * 0 and 5. Returns a move wrapped in an optional: optional is nullopt if
 * there are no legal moves from the piece at the provided index
 *
 * @param [white] team array of white pieces
 * @param [black] team array of black pieces
 * @param [turn] turn of moving piece (white = true)
 * @param [pieceIndex] piece index of team array to get move for
 * @returns nullopt if no moves for piece at provided index, bitboard
 * containg move otherwise
 */

std::optional<bitboard> getRandomMove(team& white, team& black, bool turn,
                                      int pieceIndex);

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

/*
 * Randomly plays moves until a winner, from the state specified by the
 * provided game node
 *
 * @param [node] gamenode to play from
 * @param [quiet] if false, prints board each move to stdout
 * @returns true = white win, false = black win, nullopt = draw
 */
std::optional<bool> simulate(GameNode* node, bool quiet);
