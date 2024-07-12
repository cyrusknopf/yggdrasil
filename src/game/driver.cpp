#include "game/driver.h"
#include "game/chess.h"
#include "game/inits.h"
#include "game/moves.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <optional>
#include <ostream>
#include <regex>
#include <string>
#include <tuple>
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

std::string gameStateToString(team &whitePieces, team &blackPieces) {
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

std::pair<bitboard, bitboard> takeTurn(team &white, team &black,
                                       std::string &message) {
    std::optional<bitboard> fromSquare = std::nullopt;
    std::optional<bitboard> toSquare = std::nullopt;

    while (!fromSquare.has_value() || !toSquare.has_value()) {
        clearTerm();
        std::cout << gameStateToString(white, black) << std::endl;
        std::cout << message;
        std::cout << "Please enter a move" << std::endl;
        fromSquare = readSquare();
        if (!fromSquare.has_value()) {
            std::cout << "Not a position" << std::endl;
            continue;
        }

        std::cout << "→";
        toSquare = readSquare();
        if (!toSquare.has_value()) {
            std::cout << "Not a position" << std::endl;
            continue;
        }
    }

    return std::make_pair(fromSquare.value(), toSquare.value());
}

std::tuple<bitboard, int, bitboard> takeMove(team &whiteBitboards,
                                             team &blackBitboards, bool turn,
                                             std::string &message) {
    team own;
    team opp;
    bitboard newBoard;

    // Repeat until a legal move is provided, at which point return the changed
    // board
    while (true) {
        if (turn)
            message += "\nWhite to move\n";
        else
            message += "\nBlack to move\n";

        std::pair<bitboard, bitboard> toAndFrom =
            takeTurn(whiteBitboards, blackBitboards, message);
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
            message = "No piece at from square";
            continue;
        }

        bitboard newBoard = ~(~fromBoard | fromSquare);
        newBoard = newBoard | toSquare;

        std::vector<bitboard> moves =
            pseudoLegalFromIndex(fromIdx, whiteBitboards, blackBitboards, turn);

        std::vector<bitboard>::iterator it =
            std::find(moves.begin(), moves.end(), newBoard);

        if (it == moves.end()) {
            message = "Illegal move";
            continue;
        }
        return std::make_tuple(newBoard, fromIdx, toSquare);
    }
}

std::pair<team, team> makeMove(team &whiteBitboards, team &blackBitboards,
                               bitboard toSquare, bitboard newBoard,
                               int fromIdx, bool turn) {
    team opp;
    // Update the game state, formally
    if (turn) {
        whiteBitboards[fromIdx] = newBoard;
        opp = blackBitboards;
    } else {
        blackBitboards[fromIdx] = newBoard;
        opp = whiteBitboards;
    }

    std::pair<bitboard, int> captured = findPiece(toSquare, opp);
    int capturedIdx = captured.second;

    if (capturedIdx != -1) {
        bitboard capturedBoard = captured.first;
        capturedBoard = performCapture(capturedBoard, toSquare);

        if (turn)
            blackBitboards[capturedIdx] = capturedBoard;
        else
            whiteBitboards[capturedIdx] = capturedBoard;
    }
    return std::make_pair(whiteBitboards, blackBitboards);
}

std::optional<bool> getWinner(team &white, team &black) {
    if (white.at(5) == 0)
        return false;
    else if (black.at(5) == 0)
        return true;
    else
        return std::nullopt;
}

void gameLoop() {
    std::pair<team, team> teams = initGame();
    team whiteBitboards = teams.first;
    team blackBitboards = teams.second;

    bool gameOver = false;
    bool turn = true;
    bool validMove = false;
    std::string message = "";
    std::optional<bool> winner = std::nullopt;

    team own;
    team opp;

    while (!gameOver) {
        message = "";
        std::tuple<bitboard, int, bitboard> movingPiece =
            takeMove(whiteBitboards, blackBitboards, turn, message);
        bitboard movingBoard = std::get<0>(movingPiece);
        int movingIdx = std::get<1>(movingPiece);
        bitboard movingTo = std::get<2>(movingPiece);

        std::pair<team, team> newBoards =
            makeMove(whiteBitboards, blackBitboards, movingTo, movingBoard,
                     movingIdx, turn);

        whiteBitboards = newBoards.first;
        blackBitboards = newBoards.second;

        winner = getWinner(whiteBitboards, blackBitboards);
        if (winner.has_value()) {
            gameOver = true;
        }

        turn = !turn;
    }

    std::cout << "Game over" << std::endl;
}

int main() { gameLoop(); }
