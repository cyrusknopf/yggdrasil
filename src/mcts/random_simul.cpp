#include "game/chess.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"

void fromRoot() {
    std::pair<team, team> starts = initGame();

    GameNode* root = initialiseTree(starts.first, starts.second);

    simulate(root, false);
}

void pawnCheckMate() {
    team white{1, 0, 0, 0, 0, 1 << 16};
    team black{0, 0, 0, 0, 0, 1 << 9};

    GameNode* node = initialiseTree(white, black);

    simulate(node, false);
}

int main() {
    fromRoot();
    // pawnCheckMate();
}
