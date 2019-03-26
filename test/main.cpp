#include <gtest/gtest.h>
#include "test_hashlib.hpp"
#include "test_timelib.hpp"
#include "test_logger.hpp"

/* hashlib              accepted - 2019/03/21 14:14:00
 *                      updated  - 2019/03/25 20:03:00
 * timelib              accepted - 2019/03/25 14:57:00
 * logger               accepted - 2019/03/25 19:34:00
 */

TEST(test_hashlib, case_1) {
    ASSERT_STREQ(TestSha1Case1("Hello, World!", 13), "0a0a9f2a6772942557ab5355d76af442f8f65e01");
    ASSERT_STREQ(TestSha1Case2("Hello, World!", 13).c_str(), "0a0a9f2a6772942557ab5355d76af442f8f65e01");
    ASSERT_STREQ(TestSha1Case3("Hello, World!"), "0a0a9f2a6772942557ab5355d76af442f8f65e01");
    ASSERT_STREQ(TestSha1Case4("Hello, World!").c_str(), "0a0a9f2a6772942557ab5355d76af442f8f65e01");
}

TEST(test_timelib, case_1) {
    ASSERT_GT(TestTimeCase1(), 500000);
    ASSERT_LT(TestTimeCase1(), 510000);
    ASSERT_GT(TestTimeCase2(), 500000);
    ASSERT_LT(TestTimeCase2(), 510000);
    ASSERT_FALSE(TestTimeCase3());
    ASSERT_TRUE(TestTimeCase4());
}

TEST(test_logger, case_1) {
    ASSERT_FALSE(TestLoggerCase1());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    getchar();
    return ret;
}