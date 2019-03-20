#include <gtest/gtest.h>


TEST(expect, test) {
    EXPECT_EQ(2, 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    getchar();
    return ret;
}