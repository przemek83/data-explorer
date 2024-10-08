#include <iostream>

#include <cpputils/StreamEater.h>
#include <gtest/gtest.h>

#include <src/Column.h>

TEST(ColumnTest, GetColumnTypeForName)
{
    using ColumnType = Column::ColumnType;
    bool success{false};
    ColumnType type;
    std::tie(success, type) = Column::getColumnType("string");
    EXPECT_TRUE(success);
    EXPECT_EQ(type, ColumnType::STRING);

    std::tie(success, type) = Column::getColumnType("integer");
    EXPECT_TRUE(success);
    EXPECT_EQ(type, ColumnType::INTEGER);
}

TEST(ColumnTest, GetColumnTypeForNameInvalid)
{
    StreamEater eater(std::cout);
    const auto [success, tape]{Column::getColumnType("invalid")};
    EXPECT_FALSE(success);
}