#include "utils.h"
#include <array>
#include <vector>

std::vector<bitboard> pawnPseudoLegalMoves(bitboard ownState, bitboard oppState,
                                           bitboard state, bool colour);

std::vector<bitboard> horsePseudoLegalMoves(bitboard ownState,
                                            bitboard oppState, bitboard state);

std::vector<bitboard> castlePseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state);

std::vector<bitboard> bishopPseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state);

std::vector<bitboard>
queenPseudoLegalMoves(bitboard whiteState, bitboard blackState, bitboard state);

std::vector<bitboard> kingPseudoLegalMoves(bitboard ownState, bitboard oppState,
                                           bitboard state);

std::vector<bitboard> allPseudoLegalMoves(std::array<bitboard, 6> &white,
                                          std::array<bitboard, 6> &black,
                                          bool colour);

std::vector<bitboard> pseudoLegalFromIndex(int idx,
                                           std::array<bitboard, 6> &white,
                                           std::array<bitboard, 6> &black,
                                           bool colour);
