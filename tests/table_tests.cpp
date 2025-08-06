/**
 * @file table_tests.cpp
 * @brief Tests for the Table class
 */

#include <gtest/gtest.h>
#include <tabulix/tabulix.hpp>
#include <sstream>

TEST(TableTest, EmptyTable) {
    tabulix::Table table;
    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.rowCount(), 0);
    EXPECT_EQ(table.columnCount(), 0);
    EXPECT_EQ(table.str(), "");
}

TEST(TableTest, AddHeader) {
    tabulix::Table table;
    table.addHeader({"Col1", "Col2", "Col3"});
    EXPECT_FALSE(table.empty());
    EXPECT_EQ(table.rowCount(), 1);
    EXPECT_EQ(table.columnCount(), 3);
}

TEST(TableTest, AddRow) {
    tabulix::Table table;
    table.addRow({"A", "B", "C"});
    EXPECT_FALSE(table.empty());
    EXPECT_EQ(table.rowCount(), 1);
    EXPECT_EQ(table.columnCount(), 3);

    table.addRow({"D", "E", "F"});
    EXPECT_EQ(table.rowCount(), 2);
}

TEST(TableTest, ClearTable) {
    tabulix::Table table;
    table.addHeader({"Col1", "Col2"});
    table.addRow({"A", "B"});
    EXPECT_FALSE(table.empty());

    table.clear();
    EXPECT_TRUE(table.empty());
    EXPECT_EQ(table.rowCount(), 0);
}

TEST(TableTest, SetTheme) {
    tabulix::Table table;
    table.addHeader({"Name", "Value"});
    table.addRow({"Test", "123"});

    // Test that different themes produce different output
    table.setTheme(tabulix::Theme::SIMPLE);
    std::string simpleOutput = table.str();

    table.setTheme(tabulix::Theme::UNICODE_SINGLE);
    std::string unicodeOutput = table.str();

    EXPECT_NE(simpleOutput, unicodeOutput);
}

TEST(TableTest, ColumnAlignment) {
    tabulix::Table table;
    table.addHeader({"Left", "Center", "Right"});
    table.addRow({"A", "B", "C"});

    table.setColumnAlignment(0, tabulix::Alignment::LEFT);
    table.setColumnAlignment(1, tabulix::Alignment::CENTER);
    table.setColumnAlignment(2, tabulix::Alignment::RIGHT);

    // This is a simple test to make sure setting alignments doesn't crash
    // A more comprehensive test would check the actual output formatting
    EXPECT_NO_THROW(table.str());
}

TEST(TableTest, StreamOperator) {
    tabulix::Table table;
    table.addHeader({"Test"});
    table.addRow({"Value"});

    std::stringstream ss;
    ss << table;

    EXPECT_FALSE(ss.str().empty());
    EXPECT_EQ(ss.str(), table.str());
}
