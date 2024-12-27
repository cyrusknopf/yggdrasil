#include "agents/user_agent.h"

#include <iostream>
#include <optional>
#include <string>

#include "game/chess.h"

std::optional<bitboard> UserAgent::readSquare() {
    std::string square;
    std::cin >> square;
    std::smatch matches;

    if (!std::regex_match(square, matches, squareRe)) {
        return std::nullopt;
    } else {
        return coordinateToState(square);
    }
}

std::pair<bitboard, bitboard> UserAgent::takeToAndFrom(team& white, team& black,
                                                       std::string& message) {
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

        std::cout << "↓" << std::endl;
        toSquare = readSquare();
        if (!toSquare.has_value()) {
            std::cout << "Not a position" << std::endl;
            continue;
        }
    }

    return std::make_pair(fromSquare.value(), toSquare.value());
}

std::tuple<bitboard, int, bitboard> UserAgent::takeMove(team& whiteBitboards,
                                                        team& blackBitboards,
                                                        bool turn,
                                                        std::string& message) {
    team own;
    team opp;
    bitboard newBoard;

    // Repeat until a legal move is provided, at which point return the
    // changed board
    while (true) {
        if (turn)
            message += "\nWhite to move\n";
        else
            message += "\nBlack to move\n";

        std::pair<bitboard, bitboard> toAndFrom =
            takeToAndFrom(whiteBitboards, blackBitboards, message);
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
            legalMovesFromIndex(fromIdx, whiteBitboards, blackBitboards, turn);

        std::vector<bitboard>::iterator it =
            std::find(moves.begin(), moves.end(), newBoard);

        if (it == moves.end()) {
            message = "Illegal move";
            continue;
        }
        return std::make_tuple(newBoard, fromIdx, toSquare);
    }
}

std::pair<team, team> UserAgent::takeTurn(team whiteBitboards,
                                          team blackBitboards, bool turn,
                                          std::string& message) {
    message = "";
    auto [movingBoard, movingIdx, movingTo] =
        takeMove(whiteBitboards, blackBitboards, turn, message);

    std::pair<team, team> newBoards =
        makeMove(whiteBitboards, blackBitboards, movingBoard, movingIdx, turn);

    return newBoards;
}
