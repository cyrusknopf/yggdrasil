# Yggdrasil
Bitboard chess engine with Monte Carlo tree search, written in C++
> "Yggdrasil: an immense and central tree in Norse mythology; it is the tree of life, encompassing all nine worlds"

Written with Google C++ Style in mind, so most documentaiton can be found in headers at `include/`

Currently experimenting with different optimisation techniques to improve performance of MCTS algorithm.
<!--
## Demo
<img src="demo.gif" alt="demo turn" width="200"/>
-->
## Running the engine
1. Clone the repo
2. `cd yggradasil`
3. `mkdir build`
4. `cd build/`
5. `cmake ..;make`
6. `./driver`

> Developed on Apple Silicon. For issues running on macOS set the environment variable `MallocNanoZone` to `0`
