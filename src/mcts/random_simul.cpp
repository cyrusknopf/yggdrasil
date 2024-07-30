#include <iostream>

#include "game/chess.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"

void printWinner(std::optional<bool> res) {
    if (res.has_value()) {
        if (res.value())
            std::cout << "white win" << std::endl;
        else if (!res.value())
            std::cout << "black win" << std::endl;
    } else
        std::cout << "draw" << std::endl;
}

void fromRoot() {
    std::pair<team, team> starts = initGame();

    GameNode* root = initialiseTree(starts.first, starts.second);

    std::optional<bool> res = simulate(root, false);
    printWinner(res);
}

void pawnCheckMate() {
    team white{1, 0, 0, 0, 0, 1 << 16};
    team black{0, 0, 0, 0, 0, 1 << 9};

    GameNode* node = initialiseTree(white, black);

    std::optional<bool> res = simulate(node, false);
    printWinner(res);
}

int main() {
    fromRoot();
    // pawnCheckMate();
}
