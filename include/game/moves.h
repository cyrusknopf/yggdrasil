#include "utils.h"
#include <vector>

std::vector<bitboard> pawnPseudoLegalMoves(bitboard whiteState,
                                           bitboard blackState, bitboard state,
                                           bool colour);

std::vector<bitboard> horsePseudoLegalMoves(bitboard whiteState,
                                            bitboard blackState, bitboard state,
                                            bool colour);

std::vector<bitboard> castlePseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state, bool colour);

std::vector<bitboard> bishopPseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state, bool colour);

std::vector<bitboard> queenPseudoLegalMoves(bitboard whiteState,
                                            bitboard blackState, bitboard state,
                                            bool colour);

std::vector<bitboard> kingPseudoLegalMoves(bitboard whiteState,
                                           bitboard blackState, bitboard state,
                                           bool colour);
