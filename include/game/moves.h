#include "utils.h"
#include <vector>

/*
 * Gets the pseudolegal moves for a bitboard of - possibly multiple - pawns from
 * a single pawn bitboard
 * Returns in order: single push, double push, eastwards
 * capture, westwards capture
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of pawn pieces
 * @param [colour] colour of the pawn to get moves of; white = true
 * @return vector of bitboards, each with a single unique pseudolegal move
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
 * @return vector of bitboards, each with a single unique pseudolegal move
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
 * @return vector of bitboards, each with a single unique pseudolegal move
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
 * @return vector of bitboards, each with a single unique pseudolegal move
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
 * @return vector of bitboards, each with a single unique pseudolegal move
 */
std::vector<bitboard>
queenPseudoLegalMoves(bitboard whiteState, bitboard blackState, bitboard state);

/*
 * Gets the pseudolegal moves for a bitboard of a single king from a king
 * bitboard
 * Returns in clockwise order
 *
 * @param [ownState] single bitboard of all friendly pieces
 * @param [oppState] single bitboard of all enemy pieces
 * @param [state] single bitboard of king piece
 * @return vector of bitboards, each with a single unique pseudolegal move
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
 */
std::vector<bitboard> pseudoLegalFromIndex(int idx, team &white, team &black,
                                           bool colour);
