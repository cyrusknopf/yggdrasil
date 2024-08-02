#include "game/driver.h"

#include <assert.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <optional>
#include <random>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

#include "game/chess.h"
#include "game/moves.h"
#include "mcts/backprop.h"
#include "mcts/expansion.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"
#include "mcts/selection.h"
#include "utils.h"

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

std::pair<bitboard, bitboard> takeToAndFrom(team& white, team& black,
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

std::tuple<bitboard, int, bitboard> takeMove(team& whiteBitboards,
                                             team& blackBitboards, bool turn,
                                             std::string& message) {
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

std::pair<team, team> makeMove(team& whiteBitboards, team& blackBitboards,
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

void gameLoop() {
    // General game setup
    std::pair<team, team> teams = initGame();
    team whiteBitboards = teams.first;
    team blackBitboards = teams.second;
    bool gameOver = false;
    bool turn = true;
    int halfMoveClock = 0;
    std::optional<bool> winner = std::nullopt;

    // IO setup
    std::string message = "";

    // MCTS setup
    GameNode* root = initialiseTree(whiteBitboards, blackBitboards);
    // Add all moves for white to the tree
    expansion(root);
    // Keep track of last move
    bitboard lastMove = 0;
    int ply = 0;

    // TODO add ply
    while (!gameOver && ply <= 100) {
        // User turn
        if (turn) {
            message = "";
            std::tuple<bitboard, int, bitboard> movingPiece =
                takeMove(whiteBitboards, blackBitboards, turn, message);

            bitboard movingBoard = std::get<0>(movingPiece);
            lastMove = movingBoard;
            int movingIdx = std::get<1>(movingPiece);
            bitboard movingTo = std::get<2>(movingPiece);

            std::pair<team, team> newBoards = makeSimulatedMove(
                whiteBitboards, blackBitboards, movingBoard, movingIdx, turn);

            if (!checkIfCapture(blackBitboards, newBoards.second))
                ply++;
            else
                ply = 0;

            whiteBitboards = newBoards.first;
            blackBitboards = newBoards.second;

            // Update UI for white's move
            clearTerm();
            std::cout << gameStateToString(whiteBitboards, blackBitboards)
                      << std::endl;
        }
        // Agent turn
        else {
            int gamesSimulated = 0;
            std::cout << "Agent thinking..." << std::endl;
            root = updateRootOnMove(lastMove, root);

            time_t startTime = time(NULL);
            while (time(NULL) < startTime + 15) {
                std::cout << "\rSimulated games played: " << gamesSimulated
                          << std::flush;

                GameNode* L = heursiticSelectLeaf(root);
                expansion(L);
                std::random_device rd;
                GameNode* C = nullptr;
                while (true) {
                    C = L->getRandomChild(rd());
                    if (!C->getTerminal()) break;
                }
                assert(C != nullptr);
                std::optional<bool> res = simulate(C, true);
                gamesSimulated++;
                backpropagate(C, res);
            }
            GameNode* newState = getMostVisitedChild(root);

            // Remove const for check capture
            team newWhite = newState->getWhite();

            if (!checkIfCapture(whiteBitboards, newWhite))
                ply++;
            else
                ply = 0;

            whiteBitboards = newState->getWhite();
            blackBitboards = newState->getBlack();
            root = updateRootOnMove(newState->getMove(), root);
        }

        winner = getWinner(whiteBitboards, blackBitboards);
        if (winner.has_value()) {
            gameOver = true;
        }

        turn = !turn;
    }

    std::cout << "Game over" << std::endl;
    if (!winner.has_value())
        std::cout << "Stalemate" << std::endl;
    else if (winner)
        std::cout << "White wins!" << std::endl;
    else
        std::cout << "Black wins!" << std::endl;
}

int main() { gameLoop(); }
