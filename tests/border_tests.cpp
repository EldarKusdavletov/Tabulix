/**
 * @file border_tests.cpp
 * @brief Tests for the Border class
 */

#include <gtest/gtest.h>
#include <tabulix/styling/border.hpp>

TEST(BorderTest, DefaultConstructor) {
    tabulix::Border border;
    EXPECT_EQ(border.horizontal(), "-");
    EXPECT_EQ(border.vertical(), "|");
    EXPECT_EQ(border.topLeft(), "+");
    EXPECT_EQ(border.topRight(), "+");
    EXPECT_EQ(border.bottomLeft(), "+");
    EXPECT_EQ(border.bottomRight(), "+");
    EXPECT_EQ(border.topIntersection(), "+");
    EXPECT_EQ(border.bottomIntersection(), "+");
    EXPECT_EQ(border.leftIntersection(), "+");
    EXPECT_EQ(border.rightIntersection(), "+");
    EXPECT_EQ(border.crossIntersection(), "+");
    EXPECT_TRUE(border.enabled());
}

TEST(BorderTest, CustomConstructor) {
    tabulix::Border border(
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"
    );
    EXPECT_EQ(border.horizontal(), "a");
    EXPECT_EQ(border.vertical(), "b");
    EXPECT_EQ(border.topLeft(), "c");
    EXPECT_EQ(border.topRight(), "d");
    EXPECT_EQ(border.bottomLeft(), "e");
    EXPECT_EQ(border.bottomRight(), "f");
    EXPECT_EQ(border.topIntersection(), "g");
    EXPECT_EQ(border.bottomIntersection(), "h");
    EXPECT_EQ(border.leftIntersection(), "i");
    EXPECT_EQ(border.rightIntersection(), "j");
    EXPECT_EQ(border.crossIntersection(), "k");
    EXPECT_TRUE(border.enabled());
}

TEST(BorderTest, AsciiFactory) {
    tabulix::Border border = tabulix::Border::ascii();
    EXPECT_EQ(border.horizontal(), "-");
    EXPECT_EQ(border.vertical(), "|");
    EXPECT_EQ(border.topLeft(), "+");
    EXPECT_TRUE(border.enabled());
}

TEST(BorderTest, UnicodeSingleFactory) {
    tabulix::Border border = tabulix::Border::unicodeSingle();
    EXPECT_EQ(border.horizontal(), "─");
    EXPECT_EQ(border.vertical(), "│");
    EXPECT_EQ(border.topLeft(), "┌");
    EXPECT_TRUE(border.enabled());
}

TEST(BorderTest, UnicodeDoubleFactory) {
    tabulix::Border border = tabulix::Border::unicodeDouble();
    EXPECT_EQ(border.horizontal(), "═");
    EXPECT_EQ(border.vertical(), "║");
    EXPECT_EQ(border.topLeft(), "╔");
    EXPECT_TRUE(border.enabled());
}

TEST(BorderTest, NoneFactory) {
    tabulix::Border border = tabulix::Border::none();
    EXPECT_EQ(border.horizontal(), "");
    EXPECT_EQ(border.vertical(), "");
    EXPECT_EQ(border.topLeft(), "");
    EXPECT_FALSE(border.enabled());
}
