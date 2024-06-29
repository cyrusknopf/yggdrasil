cmake_minimum_required(VERSION 3.22)

project(yggdrasil)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include)

# Gather all test source files
file(GLOB TEST_SOURCES
    tests/game/*.cpp
    tests/*.cpp
)

# Gather all source files
file(GLOB SRC_SOURCES
    src/game/*.cpp
    src/*.cpp
)

# Add the executable
add_executable(runTests ${SRC_SOURCES} ${TEST_SOURCES})

# Link libraries
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
