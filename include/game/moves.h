#ifndef _MOVES_H_
#define _MOVES_H_

#include <vector>

#include "utils.h"

struct Move {
    bitboard boardState;
    int pieceIdx;
};

/*
 * Gets the pseudolegal moves for a bitboard of - possibly multiple - pawns
 * from a single pawn bitboard Returns in order: single push, double push,
 * eastwards capture, westwards capture
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of pawn pieces
 * @param [colour] colour of the pawn to get moves of; white = true
 * @returns vector of bitboards, each with a single unique pseudolegal move
 */
std::vector<bitboard> pawnPseudoLegalMoves(bitboard ownState, bitboard oppState,
                                           bitboard state, bool colour);

/*
 * Get the pseudolegal moves for a bitboard of - possibly multiple - horses
 * from a single horse bitboard
 * Returns in order: ENN, NEE, SEE, ESS, WSS, SWW, NWW, WNN
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of horse pieces
 * @returns vector of bitboards, each with a single unique pseudolegal move
 */
std::vector<bitboard> horsePseudoLegalMoves(bitboard ownState,
                                            bitboard oppState, bitboard state);

/*
 * Gets the pseudolegal moves for a bitboard of - possibly multiple - castles
 * from a single castle bitboard
 * Returns in order: all northward, all eastward, all southward, all westward
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of castle pieces
 * @returns vector of bitboards, each with a single unique pseudolegal move
 */
std::vector<bitboard> castlePseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state);

/*
 * Gets the pseudolegal moves for a bitboard of - possibly multiple - bishops
 * from a single bishop bitboard
 * Returns in order: all northeasterly, all southeasterly, all southwesterly,
 * all northwesterly
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of bishop pieces
 * @returns vector of bitboards, each with a single unique pseudolegal move
 */
std::vector<bitboard> bishopPseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state);

/*
 * Gets the pseudolegal moves for a bitboard of - possibly multiple - queens
 * from a single queen bitboard
 * Returns in order: all northeasterly, all southeasterly, all southwesterly,
 * all northwesterly, all northward, all eastward, all southward, all westward
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of queen pieces
 * @returns vector of bitboards, each with a single unique pseudolegal move
 */
std::vector<bitboard> queenPseudoLegalMoves(bitboard whiteState,
                                            bitboard blackState,
                                            bitboard state);

/*
 * Gets the pseudolegal moves for a bitboard of a single king from a king
 * bitboard
 * Returns in clockwise order
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of king piece
 * @returns vector of bitboards, each with a single unique pseudolegal move
 */
std::vector<bitboard> kingPseudoLegalMoves(bitboard ownState, bitboard oppState,
                                           bitboard state);

/*
 * Gets the pseudolegal move of the piece specified with idx parameter
 * 0: pawn, 1:horse, 2:castle, 3:bishop, 4:queen, 5:king
 *
 * @param [idx] index of piece to get moves of
 * @param [white] reference to array of white piece bitboards
 * @param [black] reference to array of black piece bitboards
 * @param [colour] colour of piece to get moves of, white=true
 * @returns vector of bitboards, each with a single unique pseudolegal move of
 * the piece at `idx`
 */
std::vector<bitboard> pseudoLegalFromIndex(int idx, team& white, team& black,
                                           bool colour);

/*
 * Gets the legal move of the piece specified with `idx` parameter
 * 0: pawn, 1:horse, 2:castle, 3:bishop, 4:queen, 5:king
 *
 * @param [idx] index of piece to get moves of
 * @param [white] team array of white piece bitboards
 * @param [black] team array of black piece bitboards
 * @param [colour] colour of piece to get moves of, white=true
 * @returns vector of bitboards, each with a single unique legal move of
 * the piece at `idx`
 */
std::vector<bitboard> legalMovesFromIndex(int idx, team& white, team& black,
                                          bool colour);
/*
 * Searches for a piece in an array which contains a 1 at the location specified
 * in the bitboard of square
 *
 * @param [square] bitboard containing a single piece which is to be searched
 * for
 * @param [target] array of bitboards which are to be searched
 * @return pair containing <bitboard which contains the square, index of the
 * bitboard in the searched array>
 */
Move findPiece(bitboard square, std::array<bitboard, 6>& target);

/*
 * Given two team arrays, gets all the legal moves, for all pieces, for the
 * player specified by `colour`;
 *
 * @param [white] white team array
 * @param [black] black team array
 * @param [colour] player to find legal moves for: white = true
 */
std::vector<Move> getAllLegalMoves(team& white, team& black, bool colour);
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
 * Given two team arrays and the colour of the `own` team, checks whether
 * the `own` team is in check
 *
 * @param [own] team array which is checked for check
 * @param [opp] opponent team array
 * @param [colour] colour of the team which is being queried for check
 * @returns true if in check, false if not
 */
bool isOwnKingInCheck(team& own, team& opp, bool colour);

#endif  // !_MOVES_H_
