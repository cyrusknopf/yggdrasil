cmake_minimum_required(VERSION 3.22)

project(yggdrasil)

set(CMAKE_CXX_STANDARD 17)
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

# Remove driver.cpp from SRC_SOURCES
list(REMOVE_ITEM SRC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/game/driver.cpp")

# Add the executable for tests
add_executable(runTests ${SRC_SOURCES} ${TEST_SOURCES})

# Link libraries to the test executable
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Add the executable for driver.cpp and link necessary source files
add_executable(driver src/game/driver.cpp ${SRC_SOURCES})

# If the driver executable needs specific libraries, link them here
# For example, if it needs pthread:
target_link_libraries(driver pthread)
