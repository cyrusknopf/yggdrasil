#include "game/moves.h"
#include "utils.h"
#include <vector>

std::vector<bitboard> pawnPseudoLegalMoves(bitboard whiteState,
                                           bitboard blackState, bitboard state,
                                           bool colour) {
    std::vector<bitboard> moves;

    if (colour) {
        bitboard own = whiteState;
        bitboard opp = blackState;
    } else {
        bitboard own = blackState;
        bitboard opp = whiteState;
    }

    return moves;
};

std::vector<bitboard> horsePseudoLegalMoves(bitboard whiteState,
                                            bitboard blackState, bitboard state,
                                            bool colour) {
    std::vector<bitboard> moves = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    return moves;
}

/*
std::vector<bitboard> horsePseudoLegalMoves(bitboard whiteState,
                                            bitboard blackState, bitboard state,
                                            bool colour) {
    bitboard own;
    bitboard opp;
    if (colour) {
        own = whiteState;
        opp = blackState;
    } else {
        own = blackState;
        opp = whiteState;
    }

    bitboard move;
    std::vector<bitboard> moves;
    int file = getFile(state);

    if (file < 8) {
        move = slideNorthEast(slideNorth(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }

        move = slideSouthEast(slideSouth(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }
    }

    if (file < 7) {
        move = slideNorthEast(slideEast(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }

        move = slideSouthEast(slideEast(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }
    }

    if (file > 1) {
        move = slideSouthWest(slideSouth(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }

        move = slideNorthWest(slideNorth(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }
    }

    if (file > 2) {
        move = slideSouthWest(slideWest(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }

        move = slideNorthWest(slideWest(state));
        if (move != 0) {
            if ((move & own) == 0) {
                moves.push_back(move);
            }
        }
    }

    return moves;
}
*/

std::vector<bitboard> castlePseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state, bool colour) {
    std::vector<bitboard> moves;
    return moves;
};

std::vector<bitboard> bishopPseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state, bool colour) {
    std::vector<bitboard> moves;
    return moves;
};

std::vector<bitboard> queenPseudoLegalMoves(bitboard whiteState,
                                            bitboard blackState, bitboard state,
                                            bool colour) {
    std::vector<bitboard> moves;
    return moves;
};

std::vector<bitboard> kingPseudoLegalMoves(bitboard whiteState,
                                           bitboard blackState, bitboard state,
                                           bool colour) {
    std::vector<bitboard> moves;
    return moves;
};
