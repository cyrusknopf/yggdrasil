# Yggdrasil
Bitboard chess agent with Monte Carlo tree search, written in C++
<!--
> "Yggdrasil: an immense and central tree in Norse mythology; it is the tree of life, encompassing all nine worlds"
-->
Written with Google C++ Style in mind. Doxygen-style documentation can be found in headers at `include/`

<!--
## Demo
<img src="demo.gif" alt="demo turn" width="200"/>
-->
## To play against the agent
_Requirements: Docker, git_
1. `git clone git@github.com:cyrusknopf/yggdrasil.git`
2. `cd yggradasil`
3. Use provided `docker_run.sh` script to build and run the provided Docker image
4. Use provided `dr_run.sh` script to build and run the driver executable
---
> Developed on Apple Silicon. For issues running on macOS set the environment variable `MallocNanoZone` to `0`
