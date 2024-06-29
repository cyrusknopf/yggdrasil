cmake_minimum_required(VERSION 3.22)

project(yggdrasil)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} include)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests/tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
