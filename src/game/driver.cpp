#include "game/driver.h"
#include "game/inits.h"
#include "game/moves.h"
#include "utils.h"
#include <array>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

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

std::string gameStateToString(std::array<bitboard, 6> &whitePieces,
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

    return board;
}

std::string readSquare(std::array<bitboard, 6> &whitePieces,
                       std::array<bitboard, 6> &blackPieces) {
    std::string square;
    std::cin >> square;
    std::smatch matches;

    while (!std::regex_match(square, matches, squareRe)) {
        /* clearTerm(); */
        std::cout << gameStateToString(whitePieces, blackPieces);
        std::cout << std::endl;
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
        std::pair<teamBoards, teamBoards> newBoards =
            readMove(whiteBitboards, blackBitboards, turn);
        whiteBitboards = newBoards.first;
        blackBitboards = newBoards.second;
        // Always return white as the first element, black as second
        // exec move
        turn = !turn;
    }
}

int main() { gameLoop(); }
