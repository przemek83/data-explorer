#include <gtest/gtest.h>

#include <src/Operation.h>

TEST(OperationTest, GetOperationTypeForString)
{
    EXPECT_EQ(OperationType::getOperationTypeForString("avg"),
              OperationType::Type::AVG);
    EXPECT_EQ(OperationType::getOperationTypeForString("min"),
              OperationType::Type::MIN);
    EXPECT_EQ(OperationType::getOperationTypeForString("max"),
              OperationType::Type::MAX);
    EXPECT_EQ(OperationType::getOperationTypeForString("quit"),
              OperationType::Type::QUIT);
    EXPECT_EQ(OperationType::getOperationTypeForString("unknown"),
              OperationType::Type::UNKNOWN);
}

TEST(OperationTest, GetAvailableOperationsAsString)
{
    const std::string expected{"avg,max,min,quit"};
    EXPECT_EQ(OperationType::getAvailableOperationsAsString(","), expected);
}

TEST(OperationTest, ExecuteOperationAverage)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 3, 5, 7}};

    auto result{Operation<std::string>::executeOperation(
        OperationType::Type::AVG, groupingData, aggregateData)};

    EXPECT_EQ(result["group1"], 2);
    EXPECT_EQ(result["group2"], 6);
}

TEST(OperationTest, ExecuteOperationMin)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    auto result{Operation<std::string>::executeOperation(
        OperationType::Type::MIN, groupingData, aggregateData)};

    EXPECT_EQ(result["group1"], 1);
    EXPECT_EQ(result["group2"], 3);
}

TEST(OperationTest, ExecuteOperationMax)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    auto result{Operation<std::string>::executeOperation(
        OperationType::Type::MAX, groupingData, aggregateData)};

    EXPECT_EQ(result["group1"], 2);
    EXPECT_EQ(result["group2"], 4);
}

TEST(OperationTest, ExecuteOperationUnknown)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    EXPECT_THROW(Operation<std::string>::executeOperation(
                     OperationType::Type::UNKNOWN, groupingData, aggregateData),
                 std::logic_error);
}
