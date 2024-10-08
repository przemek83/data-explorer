#include <limits>
#include <string>

#include <gtest/gtest.h>

#include <src/IntegerColumn.h>
#include <src/Operation.h>

TEST(IntegerColumn, ConstructorTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    EXPECT_EQ(column.getData(), data);
}

TEST(IntegerColumn, AddDataItemTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    column.addItem("4");
    std::vector<int> expectedData{{1, 2, 3, 4}};
    EXPECT_EQ(column.getData(), expectedData);
}

TEST(IntegerColumn, AddDataItemInvalidTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    column.addItem("4");
    testing::internal::CaptureStderr();
    column.addItem("invalid");
    std::string output{testing::internal::GetCapturedStderr()};
    EXPECT_TRUE(output.find("Cannot convert to int:") != std::string::npos);
}

TEST(IntegerColumn, AddDataItemOutOfRangeTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    column.addItem("4");
    testing::internal::CaptureStderr();
    column.addItem(std::to_string(std::numeric_limits<int>::max()) + "1");
    std::string output{testing::internal::GetCapturedStderr()};
    EXPECT_TRUE(output.find("Value out of range:") != std::string::npos);
}

TEST(IntegerColumn, GetDataTest)
{
    std::vector<int> data{{1, 2, 3}};
    IntegerColumn column(data);
    EXPECT_EQ(column.getData(), data);
}

namespace
{
const IntegerColumn column{{1, 1, 2, 2, 3, 3, 4, 4}};
const std::vector<int> inputData = {3, 4, 6, 2, 7, 1, 6, 8};
}  // namespace

TEST(IntegerColumn, PerformOperationMax)
{
    const std::unordered_map<std::string, int> results{
        column.performOperation(operation::Type::MAX, inputData)};

    std::unordered_map<std::string, int> expectedResults{
        {{"2", 6}, {"1", 4}, {"3", 7}, {"4", 8}}};

    EXPECT_EQ(results, expectedResults);
}

TEST(IntegerColumn, PerformOperationMin)
{
    const std::unordered_map<std::string, int> results{
        column.performOperation(operation::Type::MIN, inputData)};

    std::unordered_map<std::string, int> expectedResults{
        {{"2", 2}, {"1", 3}, {"3", 1}, {"4", 6}}};

    EXPECT_EQ(results, expectedResults);
}

TEST(IntegerColumn, PerformOperationAvg)
{
    const std::unordered_map<std::string, int> results{
        column.performOperation(operation::Type::AVG, inputData)};

    std::unordered_map<std::string, int> expectedResults{
        {{"4", 7}, {"2", 4}, {"3", 4}, {"1", 4}}};

    EXPECT_EQ(results, expectedResults);
}