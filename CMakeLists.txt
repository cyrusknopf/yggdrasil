cmake_minimum_required(VERSION 3.22)

project(yggdrasil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include)

option(test "Build test" ON)

option(simul "Run random simulation" ON)

# Gather all test source files
set(TEST_SOURCES
    tests/utils_tests.cpp

    tests/game/moves_tests.cpp

    tests/mcts/gametree_tests.cpp
    tests/mcts/selection_tests.cpp
    tests/mcts/rollout_tests.cpp
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
    src/mcts/random_simul.cpp
)

if (test)
# Remove driver.cpp from SRC_SOURCES
list(REMOVE_ITEM SRC_SOURCES "src/game/driver.cpp")
list(REMOVE_ITEM SRC_SOURCES "src/mcts/random_simul.cpp")
# Add the executable for tests
add_executable(runTests ${SRC_SOURCES} ${TEST_SOURCES})
# Link libraries to the test executable
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

elseif (simul)
# Remove driver.cpp from SRC_SOURCES
list(REMOVE_ITEM SRC_SOURCES "src/game/driver.cpp")
add_executable(random_simul ${SRC_SOURCES})

else()
list(REMOVE_ITEM SRC_SOURCES "src/mcts/random_simul.cpp")
# Add the executable for driver.cpp and link necessary source files
add_executable(driver ${SRC_SOURCES})
endif()
