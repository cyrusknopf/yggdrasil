#include "game/moves.h"
#include "utils.h"
#include <vector>

/*
 * I opt to not use an array of function pointers for carrying out moves due to
 * the apparent inability of the compiler to perform function inlining.
 * Whether this is true or not, I am not sure, but I feel the readability of the
 * code does not suffer and possibly is even more readable when explicitly
 * listing moves.
 */

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

/*
 * Generate the pseudo legal moves for a horse piece.
 * Assumes state is a bitboard containing a single piece
 */
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

    std::vector<bitboard> pieces = getAllPieces(state);

    for (auto &piece : pieces) {

        move = slideEast(piece);
        move = slideNorth(move);
        move = slideNorth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }

        move = slideNorth(piece);
        move = slideEast(move);
        move = slideEast(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }

        move = slideSouth(piece);
        move = slideEast(move);
        move = slideEast(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }

        move = slideEast(piece);
        move = slideSouth(move);
        move = slideSouth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }

        move = slideWest(piece);
        move = slideSouth(move);
        move = slideSouth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }

        move = slideSouth(piece);
        move = slideWest(move);
        move = slideWest(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }

        move = slideNorth(piece);
        move = slideWest(move);
        move = slideWest(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }

        move = slideWest(piece);
        move = slideNorth(move);
        move = slideNorth(move);
        if (move != 0 && (move & own) == 0) {
            moves.push_back(move);
        }
    }

    return moves;
}

std::vector<bitboard> castlePseudoLegalMoves(bitboard whiteState,
                                             bitboard blackState,
                                             bitboard state, bool colour) {
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

    std::vector<bitboard> pieces = getAllPieces(state);

    for (auto &piece : pieces) {

        // Slide north
        move = state;
        while (slideNorth(move) != 0) {
            move = slideNorth(move);
            if ((move & own) != 0) {
                break;
            }
            moves.push_back(move);
            if ((move & opp) != 0) {
                break;
            }
        }

        // Slide south
        move = state;
        while (slideSouth(move) != 0) {
            move = slideSouth(move);
            if ((move & own) != 0) {
                break;
            }
            moves.push_back(move);
            if ((move & opp) != 0) {
                break;
            }
        }

        // Slide east
        move = state;
        while (slideEast(move) != 0) {
            move = slideEast(move);
            if ((move & own) != 0) {
                break;
            }
            moves.push_back(move);
            if ((move & opp) != 0) {
                break;
            }
        }

        // Slide west
        move = state;
        while (slideWest(move) != 0) {
            move = slideWest(move);
            if ((move & own) != 0) {
                break;
            }
            moves.push_back(move);
            if ((move & opp) != 0) {
                break;
            }
        }
    }
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

    move = slideNorth(state);
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    move = slideNorth(slideEast(state));
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    move = slideEast(state);
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    move = slideSouth(slideEast(state));
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    move = slideSouth(state);
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    move = slideSouth(slideWest(state));
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    move = slideWest(state);
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    move = slideNorth(slideWest(state));
    if (move != 0 && (move & own) == 0) {
        moves.push_back(move);
    }

    return moves;
};
