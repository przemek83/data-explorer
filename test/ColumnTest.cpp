#include <gtest/gtest.h>

#include <src/Column.h>

TEST(ColumnTest, GetColumnNameForType)
{
    using ColumnType = Column::ColumnType;
    EXPECT_EQ(Column::getColumnNameForType(ColumnType::STRING), "string");
    EXPECT_EQ(Column::getColumnNameForType(ColumnType::INTEGER), "integer");
}

TEST(ColumnTest, GetColumnTypeForName)
{
    using ColumnType = Column::ColumnType;
    EXPECT_EQ(Column::getColumnTypeForName("string"), ColumnType::STRING);
    EXPECT_EQ(Column::getColumnTypeForName("integer"), ColumnType::INTEGER);
}

TEST(ColumnTest, GetColumnTypeForNameInvalid)
{
    EXPECT_THROW(Column::getColumnTypeForName("unknown"), std::logic_error);
}