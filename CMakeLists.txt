cmake_minimum_required(VERSION 3.22.1)

project(yggdrasil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include)

# Locate Google Benchmark
find_package(benchmark REQUIRED)

option(test "Build test" OFF)
option(bm "Benchmark with Google benchmark" OFF)

# Set optimization flags for release mode
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()



# Gather all source files
set(SRC_SOURCES
    src/utils.cpp

    src/agents/random_agent.cpp
    src/agents/mcts_agent.cpp
    src/agents/user_agent.cpp

    src/game/chess.cpp
    src/game/driver.cpp
    src/game/moves.cpp

    src/mcts/gametree.cpp
    src/mcts/selection.cpp
    src/mcts/rollout.cpp
    src/mcts/expansion.cpp
    src/mcts/backprop.cpp
)

# Gather all test source files
set(TEST_SOURCES
    tests/utils_tests.cpp
    tests/game/moves_tests.cpp
    tests/game/chess_tests.cpp
    tests/mcts/gametree_tests.cpp
    tests/mcts/selection_tests.cpp
    tests/mcts/rollout_tests.cpp
    tests/mcts/expansion_tests.cpp
    tests/mcts/backprop_tests.cpp
)

set(BENCHMARK_SOURCES
    benchmark/mcts/rollout_benchmark.cpp
    benchmark/game/chess_benchmark.cpp
)

if (test)
  set(CMAKE_BUILD_TYPE Debug)
  # Remove driver.cpp from SRC_SOURCES
  list(REMOVE_ITEM SRC_SOURCES "src/game/driver.cpp")
  # Add the executable for test
  add_executable(runTests ${SRC_SOURCES} ${TEST_SOURCES})
  # Link libraries to the test executable
  target_link_libraries(runTests ${GTEST_LIBRARIES})
elseif (bm)
    set(CMAKE_BUILD_TYPE Release)
  # Remove other main functions
  list(REMOVE_ITEM SRC_SOURCES "src/game/driver.cpp")
  add_executable(benchmark ${SRC_SOURCES} ${BENCHMARK_SOURCES})
  target_link_libraries(benchmark benchmark::benchmark)
else()
    set(CMAKE_BUILD_TYPE Release)
  # Add the executable for driver.cpp and link necessary source files
  add_executable(driver ${SRC_SOURCES})
  target_link_libraries(driver)
endif()
