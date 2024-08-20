#include <benchmark/benchmark.h>

#include "game/chess.h"

static void BM_isMatedInitWhite(benchmark::State& state) {
    auto [white, black] = initGame();
    for (auto _ : state) isMated(white, black, true);
}
BENCHMARK(BM_isMatedInitWhite);

static void BM_isMatedInitBlack(benchmark::State& state) {
    auto [white, black] = initGame();
    for (auto _ : state) isMated(white, black, false);
}
BENCHMARK(BM_isMatedInitBlack);

static void BM_isMatedEndGame1(benchmark::State& state) {
    team white = {70940428800, 72, 128, 36, 8388608, 536870912};
    team black = {88665322160129,         4755801206503243776,
                  9295429630892703744ULL, 288371113640067072,
                  1152921504606846976,    576460752303423488};
    for (auto _ : state) isMated(white, black, false);
}
BENCHMARK(BM_isMatedEndGame1);

static void BM_isMatedEndGame2(benchmark::State& state) {
    team white = {0, 0, 9223372036854775808ULL, 0, 0, 35184372088832};
    team black = {1, 0, 0, 0, 0, 2305843009213693952};
    for (auto _ : state) isMated(white, black, false);
}
BENCHMARK(BM_isMatedEndGame2);
