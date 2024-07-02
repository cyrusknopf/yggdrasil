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
