#include "utils.h"
#include <gtest/gtest.h>

TEST(reverseU64Test, pawnStart) {
    ASSERT_EQ(0x00FF000000000000, reverseU64(0x000000000000FF00));
}

TEST(reverseU64Test, zero) { ASSERT_EQ(0, reverseU64(0)); }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(getFile, rank1file1) {
    bitboard state = 0x80;
    int file = getFile(state);
    ASSERT_EQ(1, file);
}

TEST(getFile, rank1file2) {
    bitboard state = 0x40;
    int file = getFile(state);
    ASSERT_EQ(2, file);
}

TEST(getFile, rank1file3) {
    bitboard state = 0x20;
    int file = getFile(state);
    ASSERT_EQ(3, file);
}

// TODO: Expand tests for rank

TEST(getRank, rank1file1) {
    bitboard state = 0x1;
    int rank = getRank(state);
    ASSERT_EQ(1, rank);
}

TEST(getRank, rank2file1) {
    bitboard state = 0x1000;
    int rank = getRank(state);
    ASSERT_EQ(2, rank);
}

// TODO: Expand tests for file

TEST(slideNorth, e4) {
    bitboard state = 0x0000000008000000;
    state = slideNorth(state);
    bitboard correctState = 0x0000000800000000;
    ASSERT_EQ(correctState, state);
}

TEST(slideNorth, e8) {
    bitboard state = 0x0800000000000000;
    state = slideNorth(state);
    bitboard correctState = 0;
    ASSERT_EQ(correctState, state);
}

TEST(slideSouth, e4) {
    bitboard state = 0x0000000008000000;
    state = slideSouth(state);
    bitboard correctState = 0x0000000000080000;
    ASSERT_EQ(correctState, state);
}

TEST(slideSouth, e1) {
    bitboard state = 0x0000000000000080;
    state = slideSouth(state);
    bitboard correctState = 0;
    ASSERT_EQ(correctState, state);
}
