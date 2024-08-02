cmake_minimum_required(VERSION 3.22.1)

project(yggdrasil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include)

# Locate OpenMP
find_package(OpenMP REQUIRED)

option(test "Build test" OFF)
option(simul "Run random simulation" OFF)

# Set optimization flags for release mode
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

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

# Gather all source files
set(SRC_SOURCES
    src/utils.cpp
    src/game/chess.cpp
    src/game/driver.cpp
    src/game/moves.cpp
    src/mcts/gametree.cpp
    src/mcts/selection.cpp
    src/mcts/rollout.cpp
    src/mcts/expansion.cpp
    src/mcts/backprop.cpp
    src/mcts/random_simul.cpp
)

if (test)
  # Remove driver.cpp from SRC_SOURCES
  list(REMOVE_ITEM SRC_SOURCES "src/game/driver.cpp")
  list(REMOVE_ITEM SRC_SOURCES "src/mcts/random_simul.cpp")
  # Add the executable for test
  add_executable(runTests ${SRC_SOURCES} ${TEST_SOURCES})
  # Link libraries to the test executable
  target_link_libraries(runTests ${GTEST_LIBRARIES} pthread OpenMP::OpenMP_CXX)
elseif (simul)
  # Remove driver.cpp from SRC_SOURCES
  list(REMOVE_ITEM SRC_SOURCES "src/game/driver.cpp")
  add_executable(random_simul ${SRC_SOURCES})
  target_link_libraries(random_simul OpenMP::OpenMP_CXX)
else()
  list(REMOVE_ITEM SRC_SOURCES "src/mcts/random_simul.cpp")
  # Add the executable for driver.cpp and link necessary source files
  add_executable(driver ${SRC_SOURCES})
  target_link_libraries(driver OpenMP::OpenMP_CXX)
endif()
