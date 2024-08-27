#include <gtest/gtest.h>

#include <src/IntegerColumn.h>
#include <src/Operation.h>
#include "build/googletest-src/googletest/include/gtest/gtest.h"

TEST(IntegerColumn, ConstructorTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    EXPECT_EQ(column.getData(), data);
}

TEST(IntegerColumn, GetColumnTypeTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    EXPECT_EQ(column.getColumnType(), Column::ColumnType::INTEGER);
}

TEST(IntegerColumn, AddDataItemTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    column.addDataItem("4");
    std::vector<int> expectedData{{1, 2, 3, 4}};
    EXPECT_EQ(column.getData(), expectedData);
}

TEST(IntegerColumn, AddDataItemInvalidTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    column.addDataItem("4");
    testing::internal::CaptureStderr();
    column.addDataItem("invalid");
    std::string output{testing::internal::GetCapturedStderr()};
    EXPECT_TRUE(output.find("Cannot convert to int:") != std::string::npos);
}

TEST(IntegerColumn, GetDataTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    EXPECT_EQ(column.getData(), data);
}
