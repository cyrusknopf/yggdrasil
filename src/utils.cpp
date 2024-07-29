#include "utils.h"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "game/inits.h"

int getRank(bitboard state) {
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

int getFile(bitboard state) {
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

// https://www.chessprogramming.org/Square_Attacked_By
bitboard getBetween(bitboard board1, bitboard board2) {
    const bitboard m1 = 0xFFFFFFFFFFFFFFFF;
    const bitboard a2a7 = 0x0001010101010100;
    const bitboard b2g7 = 0x0040201008040200;
    const bitboard h1b7 = 0x0002040810204080;
    // Get trainling zeros; analagous to the square index
    const int sq1 = __builtin_ctzll(board1);
    const int sq2 = __builtin_ctzll(board2);

    bitboard btwn, line, rank, file;
    btwn = (m1 << sq1) ^ (m1 << sq2);
    file = (sq2 & 7) - (sq1 & 7);
    rank = ((sq2 | 7) - sq1) >> 3;
    line = ((file & 7) - 1) & a2a7;            /* a2a7 if same file */
    line += 2 * (((rank & 7) - 1) >> 58);      /* b1g1 if same rank */
    line += (((rank - file) & 15) - 1) & b2g7; /* b2g7 if same diagonal */
    line += (((rank + file) & 15) - 1) & h1b7; /* h1b7 if same antidiag */
    line *= btwn & -btwn; /* mul acts like shift by smaller square */
    return line & btwn;   /* return the bits on that line in-between */
}

bitboard coordinateToState(const std::string& coord) {
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

std::pair<bitboard, int> findPiece(bitboard square, team& target) {
    // Ensure we are only searching for a single location
    int popcount = __builtin_popcountll(square);
    if (popcount != 1) {
        std::cout << "Tried to search with board: " << square << std::endl;
    }
    assert(__builtin_popcountll(square) == 1);
    // i to keep track of the index that we find the board at
    int i = 0;
    for (auto& board : target) {
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

std::string addPieceToStringBoard(std::string& board, bitboard pieceBitboard,
                                  const std::string& symbol) {
    std::vector<bitboard> thesePieces = getAllPieces(pieceBitboard);
    for (auto& piece : thesePieces) {
        char file = (char)(getFile(piece) + 'a' - 1);
        int rank = getRank(piece);
        std::string pos = std::string(1, file) + std::to_string(rank);
        std::regex re(pos);
        board = std::regex_replace(board, re, symbol);
    }

    return board;
}

std::string gameStateToString(team whitePieces, team blackPieces) {
    std::string board;

    for (int rank = 8; rank > 0; rank--) {
        for (char file = 'a'; file < 'i'; file++) {
            board += file;
            board += std::to_string(rank);
            board += " ";
        }
        board += "| ";
        board += std::to_string(rank);
        board += '\n';
    }
    board.append("---------------\n");
    board.append("a b c d e f g h\n");

    board = addPieceToStringBoard(board, whitePieces.at(0), WPAWN);
    board = addPieceToStringBoard(board, whitePieces.at(1), WHORSE);
    board = addPieceToStringBoard(board, whitePieces.at(2), WCASTLE);
    board = addPieceToStringBoard(board, whitePieces.at(3), WBISHOP);
    board = addPieceToStringBoard(board, whitePieces.at(4), WQUEEN);
    board = addPieceToStringBoard(board, whitePieces.at(5), WKING);

    board = addPieceToStringBoard(board, blackPieces.at(0), BPAWN);
    board = addPieceToStringBoard(board, blackPieces.at(1), BHORSE);
    board = addPieceToStringBoard(board, blackPieces.at(2), BCASTLE);
    board = addPieceToStringBoard(board, blackPieces.at(3), BBISHOP);
    board = addPieceToStringBoard(board, blackPieces.at(4), BQUEEN);
    board = addPieceToStringBoard(board, blackPieces.at(5), BKING);

    board = std::regex_replace(board, std::regex("[a-z][1-8]"), " ");

    return board;
}

// Clears terminal
void clearTerm() { std::cout << "\x1B[2J\x1B[H"; }
