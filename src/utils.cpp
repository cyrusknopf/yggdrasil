#include "utils.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

/*
 * Returns the file (column) of a piece
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return integer corresponding to the file of the piece
 */
int getFile(uint64_t state) {
    // Asserting there are not more than one piece on the board
    assert(__builtin_popcountll(state) == 1);
    // Since file is independent of rank, we shift the piece into rank 1 for
    uint64_t tempState = state;
    while (tempState > 128) {
        tempState >>= 8;
    }
    /* Find the log2 of the state. Since the state is guaranteed to be a binary
     * number with a single 1, this is correct. */
    int exp = 0;
    while ((tempState & 0b1) == 0) {
        tempState >>= 1;
        exp++;
    }
    // Subtract from 8 since files are in the inverse order than we calculate
    return 8 - exp;
}

/*
 * Returns the rank (row) of a piece
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return integer corresponding to the rank of the piece
 */
int getRank(uint64_t state) {
    // Asserting there are not more than one piece on the board
    assert(__builtin_popcountll(state) == 1);
    // Shift downwards until we reach 0
    int rank = 0;
    uint64_t tempState = state;
    while (tempState != 0) {
        tempState >>= 8;
        rank++;
    }
    return rank;
}

/*
 * Moves the provided piece north one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved up one square
 */
bitboard slideNorth(bitboard state) {
    assert(__builtin_popcountll(state) == 1);
    return state <<= 8;
}

/*
 * Moves the provided piece south one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved down one square
 */
bitboard slideSouth(bitboard state) {
    assert(__builtin_popcountll(state) == 1);
    return state >>= 8;
}

/*
 * Moves the provided piece east one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved right one square
 */
bitboard slideEast(bitboard state) {
    assert(__builtin_popcountll(state) == 1);
    return (state >>= 1) & 0x7F7F7F7F7F7F7F7FULL;
}

/*
 * Moves the provided piece west one square and returns it
 *
 * @param [state] bitboard with a single piece (single 1)
 * @return bitboard with the piece moved left one square
 */
uint64_t slideWest(uint64_t state) {
    assert(__builtin_popcountll(state) == 1);
    return (state <<= 1) & 0xFEFEFEFEFEFEFEFE;
}

/*
 * Returns an array of bitboards, each with a single piece, from a bitboard with
 * multiple pieces
 *
 * @param [state] bitboard with multiple pieces, which each piece will be
 * extracted from
 * @return vector of bitboards, each with a single piece from the original board
 * on it
 */
std::vector<bitboard> getAllPieces(bitboard state) {
    bitboard initState = state;
    std::vector<bitboard> pieces;
    while (initState != 0) {
        bitboard thisPiece = initState & -initState;
        pieces.push_back(thisPiece);
        initState &= initState - 1;
    }
    return pieces;
}

/*
 * Given a chess coordinate (e.g. a3) in string form, returns a bitboard with a
 * single piece at that coordinate
 *
 * @param [coord] coordinate in string form
 * @return bitboard with a 1 at the coordinate only
 */
bitboard coordinateToState(const std::string &coord) {
    // Get rank and file to determine how many times we must shift
    int file = coord.at(0) - 'a';
    int rank = coord.at(1) - '1';

    // Start at h1 i.e. bottom right
    bitboard state = 1;

    // Shift the appropriate number of times left and up
    for (int j = 0; j < 7 - file; j++) {
        state = slideWest(state);
    }
    for (int i = 0; i < rank; i++) {
        state = slideNorth(state);
    }

    return state;
}

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
std::pair<bitboard, int> findPiece(bitboard square, team &target) {
    // Ensure we are only searching for a single location
    assert(__builtin_popcountll(square) == 1);
    int i = 0;
    for (auto &board : target) {
        if ((board & square) != 0) {
            return std::make_pair(board, i);
        }
        i++;
    }
    return std::make_pair(0, -1);
}

/*
 * Capture logic for a board containing possibly many pieces (victim), and a
 * single piece (captor) which will capture one of those pieces. Returns victim
 * after capture
 *
 * @param [victim] bitboard to be captured
 * @param [captor] bitboard with a single piece, will capture one of victim's
 * pieces
 * @return victim after capture
 */
bitboard performCapture(bitboard victim, bitboard captor) {
    assert((victim & captor) != 0);
    assert(__builtin_popcountll(captor) == 1);
    return (victim & ~captor);
}

// Clears terminal
void clearTerm() { std::cout << "\x1B[2J\x1B[H"; }
