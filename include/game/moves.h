#include "utils.h"
#include <array>
#include <vector>

std::vector<bitboard> pawnPseudoLegalMoves(std::array<bitboard, 6> whiteState,
                                           std::array<bitboard, 6> blackState,
                                           bitboard state, bool colour);

std::vector<bitboard> horsePseudoLegalMoves(std::array<bitboard, 6> whiteState,
                                            std::array<bitboard, 6> blackState,
                                            bitboard state, bool colour);

std::vector<bitboard> castlePseudoLegalMoves(std::array<bitboard, 6> whiteState,
                                             std::array<bitboard, 6> blackState,
                                             bitboard state, bool colour);

std::vector<bitboard> bishopPseudoLegalMoves(std::array<bitboard, 6> whiteState,
                                             std::array<bitboard, 6> blackState,
                                             bitboard state, bool colour);

std::vector<bitboard> queenPseudoLegalMoves(std::array<bitboard, 6> whiteState,
                                            std::array<bitboard, 6> blackState,
                                            bitboard state, bool colour);

std::vector<bitboard> kingPseudoLegalMoves(std::array<bitboard, 6> whiteState,
                                           std::array<bitboard, 6> blackState,
                                           bitboard state, bool colour);
