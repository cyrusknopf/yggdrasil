#include "game/driver.h"

#include <cstdlib>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <utility>

#include "agents/mcts_agent.h"
#include "agents/random_agent.h"
#include "agents/user_agent.h"
#include "game/chess.h"
#include "game/moves.h"
#include "mcts/backprop.h"
#include "mcts/expansion.h"
#include "mcts/gametree.h"

void clearAndPrintState(team white, team black) {
    clearTerm();
    std::cout << gameStateToString(white, black) << std::endl;
}

void printWinner(std::optional<bool> winner) {
    std::cout << "\nGame over" << std::endl;
    if (!winner.has_value())
        std::cout << "Stalemate" << std::endl;
    else if (winner)
        std::cout << "White wins!" << std::endl;
    else
        std::cout << "Black wins!" << std::endl;
}

int updateHalfMoveClock(team oldTeam, team newTeam, int clock) {
    if (!checkIfCapture(oldTeam, newTeam))
        clock++;
    else
        clock = 0;

    return clock;
}

void userVsMCTS(int moveTime) {
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

    // User setup
    UserAgent usrAgent = UserAgent();

    // MCTS setup
    GameNode* root = initialiseTree(whiteBitboards, blackBitboards);
    std::random_device rd;
    // Add all moves for white to the tree
    expansion(root);
    MCTSAgent mctsAgent = MCTSAgent(moveTime, (int)rd());

    while (!gameOver && halfMoveClock <= 100) {
        // User turn
        if (turn) {
            clearAndPrintState(whiteBitboards, blackBitboards);

            auto [newWhite, newBlack] = UserAgent().takeTurn(
                whiteBitboards, blackBitboards, turn, message);

            halfMoveClock =
                updateHalfMoveClock(blackBitboards, newBlack, halfMoveClock);

            whiteBitboards = newWhite;
            blackBitboards = newBlack;

        }
        // Agent turn
        else {
            clearAndPrintState(whiteBitboards, blackBitboards);

            root =
                mctsAgent.takeTurn(root, whiteBitboards, blackBitboards, false);

            halfMoveClock = updateHalfMoveClock(
                whiteBitboards, root->getWhite(), halfMoveClock);

            whiteBitboards = root->getWhite();
            blackBitboards = root->getBlack();
        }

        winner = getWinner(whiteBitboards, blackBitboards);
        if (winner.has_value()) gameOver = true;
        turn = !turn;
    }
    printWinner(winner);
}

void randomVsMCTS(int moveTime) {
    // General game setup
    std::pair<team, team> teams = initGame();
    team whiteBitboards = teams.first;
    team blackBitboards = teams.second;
    bool gameOver = false;
    bool turn = true;
    int halfMoveClock = 0;
    std::optional<bool> winner = std::nullopt;

    // MCTS setup
    GameNode* root = initialiseTree(whiteBitboards, blackBitboards);
    std::random_device rd;
    // Add all moves for white to the tree
    expansion(root);
    MCTSAgent mctsAgent = MCTSAgent(moveTime, (int)rd());

    // Random Agent
    RandomAgent rdmAgent = RandomAgent();

    while (!gameOver && halfMoveClock <= 100) {
        // Random agent turn
        if (turn) {
            clearAndPrintState(whiteBitboards, blackBitboards);

            auto [newWhite, newBlack] =
                rdmAgent.takeTurn(whiteBitboards, blackBitboards, turn);

            halfMoveClock =
                updateHalfMoveClock(blackBitboards, newBlack, halfMoveClock);

            whiteBitboards = newWhite;
            blackBitboards = newBlack;
        }
        // MCTS agent turn
        else {
            clearAndPrintState(whiteBitboards, blackBitboards);

            root =
                mctsAgent.takeTurn(root, whiteBitboards, blackBitboards, false);

            halfMoveClock = updateHalfMoveClock(
                whiteBitboards, root->getWhite(), halfMoveClock);

            whiteBitboards = root->getWhite();
            blackBitboards = root->getBlack();
        }

        winner = getWinner(whiteBitboards, blackBitboards);
        if (winner.has_value()) gameOver = true;

        turn = !turn;
    }
    printWinner(winner);
}

int main(int argc, char* argv[]) {
    int moveTime;
    if (argc != 2)
        exit(1);
    else
        moveTime = atoi(argv[1]);
    randomVsMCTS(moveTime);
    // userVsMCTS(moveTime);
}
