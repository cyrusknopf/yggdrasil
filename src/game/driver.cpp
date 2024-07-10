#include "game/driver.h"
#include "game/chess.h"
#include "game/inits.h"
#include "game/moves.h"
#include "utils.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <optional>
#include <ostream>
#include <regex>
#include <string>
#include <unistd.h>
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

std::optional<bitboard> readSquare() {
    std::string square;
    std::cin >> square;
    std::smatch matches;

    if (!std::regex_match(square, matches, squareRe)) {
        return std::nullopt;
    } else {
        return coordinateToState(square);
    }
}

std::pair<bitboard, bitboard> takeTurn(team &white, team &black) {
    std::optional<bitboard> fromSquare = std::nullopt;
    std::optional<bitboard> toSquare = std::nullopt;

    while (!fromSquare.has_value() || !toSquare.has_value()) {
        std::cout << gameStateToString(white, black) << std::endl;
        std::cout << "Please enter from square" << std::endl;
        fromSquare = readSquare();
        if (!fromSquare.has_value()) {
            std::cout << "Not a position" << std::endl;
            continue;
        }

        std::cout << "Please enter to square" << std::endl;
        toSquare = readSquare();
        if (!toSquare.has_value()) {
            std::cout << "Not a position" << std::endl;
            continue;
        }
    }

    return std::make_pair(fromSquare.value(), toSquare.value());
}

void gameLoop() {
    std::pair<team, team> teams = initGame();
    team whiteBitboards = teams.first;
    team blackBitboards = teams.second;

    bool gameOver = false;
    bool turn = true;
    bool validMove = false;

    team own;
    team opp;

    while (!validMove) {
        std::pair<bitboard, bitboard> toAndFrom =
            takeTurn(whiteBitboards, blackBitboards);
        bitboard fromSquare = toAndFrom.first;
        bitboard toSquare = toAndFrom.second;

        if (turn) {
            own = whiteBitboards;
            opp = blackBitboards;
        } else {
            own = blackBitboards;
            opp = whiteBitboards;
        }

        std::pair<bitboard, int> fromPiece = findPiece(fromSquare, own);
        bitboard fromBoard = fromPiece.first;
        bitboard fromIdx = fromPiece.second;

        if (fromIdx == -1) {
            std::cout << "No piece at from square" << std::endl;
            continue;
        }

        bitboard newBoard = ~(~fromBoard | fromSquare);
        newBoard = newBoard | toSquare;
        std::cout << "newboard:" << newBoard << std::endl;

        std::vector<bitboard> moves =
            pseudoLegalFromIndex(fromIdx, whiteBitboards, blackBitboards, turn);
        for (auto &move : moves) {
            std::cout << "MOVE : " << move << std::endl;
        }

        std::vector<bitboard>::iterator it =
            std::find(moves.begin(), moves.end(), newBoard);

        if (it == moves.end()) {
            std::cout << "Illegal move" << std::endl;
            continue;
        }
    }

    /* while (!gameOver) { */
    /*     // Always return white as the first element, black as second */
    /*     // exec move */
    /*     turn = !turn; */
    /* } */
}

int main() { gameLoop(); }
