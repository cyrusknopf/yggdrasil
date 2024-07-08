#include "game/inits.h"
#include "game/moves.h"
#include "utils.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

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

std::string readSquare(std::array<bitboard, 6> &whitePieces,
                       std::array<bitboard, 6> &blackPieces) {
    std::string square;
    std::cin >> square;
    std::smatch matches;

    while (!std::regex_match(square, matches, squareRe)) {
        /* clearTerm(); */
        printGameState(whitePieces, blackPieces);
        std::cout << "\n";
        std::cin >> square;
    }

    return square;
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

/*
 *      1111
 *      1000
 *
 *      1 and 1 = 0
 *      1 and 0 = 1
 *      0 and 1 = 0
 *      0 and 0 = 0
 *
 */
bitboard performCapture(bitboard victim, bitboard captor) {

    return ~(victim & ~captor);
}

std::pair<std::array<bitboard, 6>, std::array<bitboard, 6>>
readMove(std::array<bitboard, 6> &whitePieces,
         std::array<bitboard, 6> &blackPieces, bool turn) {

    // XXX This cant be good, own and opp are declared as arrays but then
    // assigned references
    std::array<bitboard, 6> own;
    std::array<bitboard, 6> opp;
    if (turn) {
        own = whitePieces;
        opp = blackPieces;
    } else {
        own = blackPieces;
        opp = whitePieces;
    }

    // Getting the bitboard (and by extension, piece) that is being moved
    std::string from;
    bitboard fromBoard;
    int boardIndex = -1;

    // Continue requesting a piece if the user selects a square with no piece
    while (boardIndex == -1) {
        // XXX Using white/black here instead of own/opp because the order of
        // arguments matters
        std::cout << "Enter from square\n";
        std::string from = readSquare(whitePieces, blackPieces);
        bitboard fromBoard = coordinateToState(from);
        std::pair<bitboard, int> p = findPiece(fromBoard, own);
        fromBoard = p.first;
        boardIndex = p.second;

        // Handle first case
        if (boardIndex == -1) {
            std::cout << "Please enter a square with a piece on it\n";
            continue;
        }

        // XOR the piece which is being moved with the board with the moving
        // piece start position
        bitboard newBoard = own.at(boardIndex) ^= fromBoard;

        std::vector<bitboard> moves =
            pseudoLegalFromIndex(boardIndex, own, opp, turn);

        for (auto &move : moves) {
            std::cout << move << std::endl;
        }
        std::vector<bitboard>::iterator it;

        std::cout << "Enter to square\n";
        std::string to = readSquare(whitePieces, blackPieces);
        bitboard toBoard = coordinateToState(to);
        // OR the board with a 0 at the origin position of the moving piece with
        // a board with a 1 at the destination
        newBoard |= toBoard;
        // Search for the board in the legal moves
        it = find(moves.begin(), moves.end(), newBoard);

        // If the move isn't in the psuedo legal ones, request new move
        if (it == moves.end()) {
            std::cout << "Please enter a legal move\n";
            boardIndex = -1;
            continue;
        }

        own[boardIndex] = newBoard;

        std::pair<bitboard, int> captureInfo = findPiece(toBoard, opp);
        int captureIndex = captureInfo.second;

        if (captureIndex != -1) {
            bitboard victim = captureInfo.second;
            // XXX This uses the board with a sole 1 at the moved location to
            // capture. Should be identical to using newBoard, right?
            bitboard capturedBoard = performCapture(victim, toBoard);
            opp[captureIndex] = victim;
        }
    }

    // Always return white as the first element, black as second
    if (turn) {
        return std::make_pair(own, opp);
    } else {
        return std::make_pair(opp, own);
    }
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
