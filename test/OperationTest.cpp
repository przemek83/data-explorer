#include <gtest/gtest.h>

#include <src/Operation.h>
#include <src/OperationType.h>

TEST(OperationTest, GetoperationTypeForString)
{
    EXPECT_EQ(operationType::getOperationTypeForString("avg"),
              operationType::Type::AVG);
    EXPECT_EQ(operationType::getOperationTypeForString("min"),
              operationType::Type::MIN);
    EXPECT_EQ(operationType::getOperationTypeForString("max"),
              operationType::Type::MAX);
    EXPECT_EQ(operationType::getOperationTypeForString("quit"),
              operationType::Type::QUIT);
    EXPECT_EQ(operationType::getOperationTypeForString("unknown"),
              operationType::Type::UNKNOWN);
}

TEST(OperationTest, GetAvailableOperationsAsString)
{
    const std::string expected{"avg,max,min,quit"};
    EXPECT_EQ(operationType::getAvailableOperationsAsString(","), expected);
}

TEST(OperationTest, ExecuteOperationAverage)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 3, 5, 7}};

    const auto [success, results]{Operation<std::string>::executeOperation(
        operationType::Type::AVG, groupingData, aggregateData)};

    EXPECT_TRUE(success);
    EXPECT_EQ(results.at("group1"), 2);
    EXPECT_EQ(results.at("group2"), 6);
}

TEST(OperationTest, ExecuteOperationMin)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    const auto [success, results]{Operation<std::string>::executeOperation(
        operationType::Type::MIN, groupingData, aggregateData)};

    EXPECT_TRUE(success);
    EXPECT_EQ(results.at("group1"), 1);
    EXPECT_EQ(results.at("group2"), 3);
}

TEST(OperationTest, ExecuteOperationMax)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    const auto [success, results]{Operation<std::string>::executeOperation(
        operationType::Type::MAX, groupingData, aggregateData)};

    EXPECT_TRUE(success);
    EXPECT_EQ(results.at("group1"), 2);
    EXPECT_EQ(results.at("group2"), 4);
}

TEST(OperationTest, ExecuteOperationUnknown)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    const auto [success, results]{Operation<std::string>::executeOperation(
        operationType::Type::UNKNOWN, groupingData, aggregateData)};

    EXPECT_FALSE(success);
    EXPECT_TRUE(results.empty());
}
