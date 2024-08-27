#include <gtest/gtest.h>

#include <src/Operation.h>
#include <src/StringColumn.h>

TEST(StringColumnTest, GetColumnType)
{
    StringColumn stringColumn;
    EXPECT_EQ(stringColumn.getColumnType(), Column::ColumnType::STRING);
}

TEST(StringColumn, AddDataItem)
{
    StringColumn stringColumn;
    stringColumn.addDataItem("apple");
    stringColumn.addDataItem("banana");
    stringColumn.addDataItem("apple");  // Duplicate

    const std::vector<unsigned int>& data{stringColumn.getData()};
    ASSERT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 1);  // Duplicate should map to the same ID
}

TEST(StringColumn, GetData)
{
    StringColumn stringColumn;
    stringColumn.addDataItem("apple");
    stringColumn.addDataItem("banana");

    const std::vector<unsigned int>& data{stringColumn.getData()};
    ASSERT_EQ(data.size(), 2);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
}

TEST(StringColumn, PerformOperation)
{
    StringColumn stringColumn;
    stringColumn.addDataItem("apple");
    stringColumn.addDataItem("banana");
    stringColumn.addDataItem("apple");
    stringColumn.addDataItem("banana");

    std::vector<int> inputData = {3, 4, 6, 2};
    const auto results{stringColumn.performOperation(
        Operation::OperationType::MAX, inputData)};

    std::unordered_map<std::string, int> expectedResults{
        {{"apple", 6}, {"banana", 4}}};

    EXPECT_EQ(results, expectedResults);
}
