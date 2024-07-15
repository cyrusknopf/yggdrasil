#include "utils.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

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

bitboard slideNorth(bitboard state) { return state <<= 8; }

bitboard slideSouth(bitboard state) { return state >>= 8; }

bitboard slideEast(bitboard state) {
    return (state >>= 1) & 0x7F7F7F7F7F7F7F7FULL;
}

uint64_t slideWest(uint64_t state) {
    return (state <<= 1) & 0xFEFEFEFEFEFEFEFE;
}

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

bitboard performCapture(bitboard victim, bitboard captor) {
    assert((victim & captor) != 0);
    assert(__builtin_popcountll(captor) == 1);
    return (victim & ~captor);
}

// Clears terminal
void clearTerm() { std::cout << "\x1B[2J\x1B[H"; }
