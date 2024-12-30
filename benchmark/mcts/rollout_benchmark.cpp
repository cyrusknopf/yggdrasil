#include <benchmark/benchmark.h>

#include "game/chess.h"
#include "mcts/gametree.h"
#include "mcts/rollout.h"

static void BM_simulateInit(benchmark::State& state) {
    auto [white, black] = initGame();
    GameNode* root = initialiseTree(white, black);
    int seed = 42;
    for (auto _ : state) simulate(root, seed);
}

BENCHMARK(BM_simulateInit);

BENCHMARK_MAIN();
