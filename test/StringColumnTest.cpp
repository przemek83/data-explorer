#include <gtest/gtest.h>

#include <src/Operation.h>
#include <src/StringColumn.h>

TEST(StringColumn, AddDataItem)
{
    StringColumn stringColumn;
    stringColumn.addItem("apple");
    stringColumn.addItem("banana");
    stringColumn.addItem("apple");  // Duplicate

    const std::vector<int>& data{stringColumn.getData()};
    ASSERT_EQ(data.size(), 3);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 1);  // Duplicate should map to the same ID
}

TEST(StringColumn, GetData)
{
    StringColumn stringColumn;
    stringColumn.addItem("apple");
    stringColumn.addItem("banana");

    const std::vector<int>& data{stringColumn.getData()};
    ASSERT_EQ(data.size(), 2);
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
}

namespace
{
StringColumn getStringColumn()
{
    StringColumn stringColumn;
    stringColumn.addItem("apple");
    stringColumn.addItem("banana");
    stringColumn.addItem("apple");
    stringColumn.addItem("banana");
    return stringColumn;
}
const std::vector<int> inputData = {3, 4, 6, 2};
}  // namespace

TEST(StringColumn, PerformOperationMax)
{
    StringColumn stringColumn{getStringColumn()};
    const auto results{
        stringColumn.performOperation(operation::Type::MAX, inputData)};

    std::unordered_map<std::string, int> expectedResults{
        {{"apple", 6}, {"banana", 4}}};

    EXPECT_EQ(results, expectedResults);
}

TEST(StringColumn, PerformOperationMin)
{
    StringColumn stringColumn{getStringColumn()};
    const auto results{
        stringColumn.performOperation(operation::Type::MIN, inputData)};

    std::unordered_map<std::string, int> expectedResults{
        {{"apple", 3}, {"banana", 2}}};

    EXPECT_EQ(results, expectedResults);
}

TEST(StringColumn, PerformOperationAvg)
{
    StringColumn stringColumn{getStringColumn()};
    const auto results{
        stringColumn.performOperation(operation::Type::AVG, inputData)};

    std::unordered_map<std::string, int> expectedResults{
        {{"apple", 5}, {"banana", 3}}};

    EXPECT_EQ(results, expectedResults);
}