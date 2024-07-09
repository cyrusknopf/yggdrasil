#include "utils.h"
#include <cstdint>
#include <immintrin.h>
#include <iostream>
#include <vector>

uint64_t reverseU64(uint64_t X) { return __bswap_64(X); }

int getFile(uint64_t state) {
    /*
     * Since file is independent of rank, we shift the piece into rank 1 for
     * simplicity
     */
    uint64_t tempState = state;
    while (tempState > 128) {
        tempState >>= 8;
    }

    /*
     * Find the log2 of the state. Since the state is guaranteed to be a binary
     * number with a single 1, this is correct.
     */
    int exp = 0;
    while ((tempState & 0b1) == 0) {
        tempState >>= 1;
        exp++;
    }

    return 8 - exp;
}

int getRank(uint64_t state) {
    int rank = 0;
    uint64_t tempState = state;
    while (tempState != 0) {
        tempState >>= 8;
        rank++;
    }
    return rank;
}

bitboard coordinateToState(const std::string &coord) {
    int file = coord.at(0) - 'a';
    int rank = coord.at(1) - '1';

    bitboard state = 1;

    for (int j = 0; j < 7 - file; j++) {
        state = slideWest(state);
    }

    for (int i = 0; i < rank; i++) {
        state = slideNorth(state);
    }

    return state;
}

uint64_t slideNorth(uint64_t state) { return state <<= 8; }
uint64_t slideEast(uint64_t state) {
    return (state >>= 1) & 0x7F7F7F7F7F7F7F7FULL;
}
uint64_t slideSouth(uint64_t state) { return state >>= 8; }
uint64_t slideWest(uint64_t state) {
    return (state <<= 1) & 0xFEFEFEFEFEFEFEFE;
}

// uint64_t slideNorthWest(uint64_t state) { return state <<= 9; }
// uint64_t slideSouthWest(uint64_t state) { return state >>= 7; }
// uint64_t slideNorthEast(uint64_t state) { return state <<= 7; }
// uint64_t slideSouthEast(uint64_t state) { return state >>= 9; }

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

std::pair<bitboard, int> findPiece(bitboard square,
                                   std::array<bitboard, 6> &target) {
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

    return ~(victim & ~captor);
}

void clearTerm() { std::cout << "\x1B[2J\x1B[H"; }
