#include "game/driver.h"
#include "utils.h"
#include <gtest/gtest.h>
#include <string>

TEST(coordinateToState, e4) {
    std::string coordinate = "e4";
    bitboard state = coordinateToState("e4");
    bitboard correct = 0x8000000;

    ASSERT_EQ(correct, state);
}
