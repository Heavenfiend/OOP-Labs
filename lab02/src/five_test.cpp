#include "Five.h"
#include "gtest/gtest.h"

TEST(FiveTest, CreateFromString) {
    Five a("42");
    EXPECT_EQ(a.toDecimal(), 22);
}
// 12332
TEST(FiveTest, CreateFromDecimal) {
    Five a(22);
    EXPECT_EQ(a.toDecimal(), 22);
}
//12 321312
TEST(FiveTest, AddTwoNumbers) {
    Five a("42");
    Five b("34");
    Five c = a.add(b);
    EXPECT_EQ(c.toDecimal(), 41);
}

TEST(FiveTest, SubtractTwoNumbers) {
    Five a("42"); // 1233333
    Five b("34");
    Five c = a.subtract(b);
    EXPECT_EQ(c.toDecimal(), 3);
}

TEST(FiveTest, SubResultZero) {
    Five a("34");
    Five b("42");
    Five c = a.subtract(b);
    EXPECT_EQ(c.toDecimal(), 0);
}

TEST(FiveTest, LessThan) {
    Five a("34"); // 12333 да тут так
    Five b("42");
    EXPECT_TRUE(a.less(b));
}

TEST(FiveTest, GreaterThan) {
    Five a("42");
    Five b("34");
    EXPECT_TRUE(a.greater(b));
}

TEST(FiveTest, Equals) {
    Five a("42");
    Five b("42");
    EXPECT_TRUE(a.equals(b));
}

TEST(FiveTest, InvalidString) {
    EXPECT_THROW(Five("125"), std::invalid_argument);
    EXPECT_THROW(Five("abc"), std::invalid_argument);
}

// лишний тест, чтобы было "похоже"
TEST(FiveTest, ToStringTest) {
    Five a("123");
    EXPECT_EQ(a.toString(), "123");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}