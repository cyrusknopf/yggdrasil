#include "game/inits.h"
#include "utils.h"
#include <array>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

bitboard coordinateToState(std::string coord) {
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

std::string addPieceToStringBoard(std::string &board, bitboard pieceBitboard,
                                  const std::string &symbol) {
    std::vector<bitboard> thesePieces = getAllPieces(pieceBitboard);
    for (auto &piece : thesePieces) {
        char file = (char)(getFile(piece) + 'a' - 1);
        int rank = getRank(piece);
        std::string pos = std::string(1, file) + std::to_string(rank);
        std::regex re(pos);
        board = std::regex_replace(board, re, symbol);
    }

    return board;
}

void printGameState(std::array<bitboard, 6> &whitePieces,
                    std::array<bitboard, 6> &blackPieces) {

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
    board = addPieceToStringBoard(board, whitePieces.at(5), WQUEEN);

    board = addPieceToStringBoard(board, blackPieces.at(0), BPAWN);
    board = addPieceToStringBoard(board, blackPieces.at(1), BHORSE);
    board = addPieceToStringBoard(board, blackPieces.at(2), BCASTLE);
    board = addPieceToStringBoard(board, blackPieces.at(3), BBISHOP);
    board = addPieceToStringBoard(board, blackPieces.at(4), BQUEEN);
    board = addPieceToStringBoard(board, blackPieces.at(5), BQUEEN);

    board = std::regex_replace(board, std::regex("[a-z][1-8]"), " ");

    std::cout << board;
    return;
}

std::string readSquare(std::array<bitboard, 6> whitePieces,
                       std::array<bitboard, 6> blackPieces) {
    std::string square;
    std::cin >> square;
    std::smatch matches;

    while (!std::regex_match(square, matches, squareRe)) {
        clearTerm();
        printGameState(whitePieces, blackPieces);
        std::cin >> square;
    }

    return square;
}

void gameLoop() {
    std::array<bitboard, 6> whiteBitboards = {whitePawnInit,   whiteHorseInit,
                                              whiteCastleInit, whiteBishopInit,
                                              whiteQueenInit,  whiteKingInit};

    // TODO Change these to contants
    std::array<bitboard, 6> blackBitboards = {
        reverseU64(whitePawnInit),   reverseU64(whiteHorseInit),
        reverseU64(whiteCastleInit), reverseU64(whiteBishopInit),
        reverseU64(whiteQueenInit),  reverseU64(whiteKingInit)};

    bool gameOver = false;
    bool turn = true;

    while (!gameOver) {
        std::string from = readSquare(whiteBitboards, blackBitboards);
        std::string to = readSquare(whiteBitboards, blackBitboards);
        std::cout << "done";
    }
}

int main() { gameLoop(); }
