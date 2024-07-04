#include "game/inits.h"
#include "utils.h"
#include <array>
#include <iostream>
#include <regex>
#include <string>

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

std::string readSquare() {
    std::string square;
    std::cin >> square;
    std::smatch matches;

    while (!std::regex_match(square, matches, squareRe)) {
        clearTerm();
        std::cout << "here is the game\n";
        std::cin >> square;
    }

    return square;
}

void printGameState(std::array<bitboard, 6> whitePieces,
                    std::array<bitboard, 6> blackPieces) {
    return;
    return;
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
        std::string from = readSquare();
        std::string to = readSquare();
        std::cout << "done";
    }
}

int main() { gameLoop(); }
