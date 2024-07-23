# Yggdrasil
Bitboard chess engine written in C++

Currently impelemting Monte Carlo Tree Search

Priortising MCTS over en passant and castling

## Running the engine
1. Clone the repo
2. `cd yggradasil`
3. `mkdir build`
4. `cd build/`
5. `cmake -Dtest=OFF -Dsimul=OFF..;make`
6. `./driver`

> Developed on Apple Silicon. For issues running on macOS set the environment variable `MallocNanoZone` to `0`
