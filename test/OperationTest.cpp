#include <cpputils/StreamEater.h>
#include <gtest/gtest.h>

#include <src/Operation.h>

TEST(OperationTest, GetoperationTypeForString)
{
    EXPECT_EQ(operation::getOperationTypeForString("AVG"),
              operation::Type::AVG);
    EXPECT_EQ(operation::getOperationTypeForString("MIN"),
              operation::Type::MIN);
    EXPECT_EQ(operation::getOperationTypeForString("MAX"),
              operation::Type::MAX);
    EXPECT_EQ(operation::getOperationTypeForString("QUIT"),
              operation::Type::QUIT);
    EXPECT_EQ(operation::getOperationTypeForString("UNKNOWN"),
              operation::Type::UNKNOWN);
}

TEST(OperationTest, GetAvailableOperationsAsString)
{
    const std::string expected{"avg,max,min,quit"};
    EXPECT_EQ(operation::getAvailableOperationsAsString(","), expected);
}

TEST(OperationTest, ExecuteOperationAverage)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 3, 5, 7}};

    const auto [success, results]{operation::executeOperation(
        operation::Type::AVG, groupingData, aggregateData)};

    EXPECT_TRUE(success);
    EXPECT_EQ(results.at("group1"), 2);
    EXPECT_EQ(results.at("group2"), 6);
}

TEST(OperationTest, ExecuteOperationMin)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    const auto [success, results]{operation::executeOperation(
        operation::Type::MIN, groupingData, aggregateData)};

    EXPECT_TRUE(success);
    EXPECT_EQ(results.at("group1"), 1);
    EXPECT_EQ(results.at("group2"), 3);
}

TEST(OperationTest, ExecuteOperationMax)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    const auto [success, results]{operation::executeOperation(
        operation::Type::MAX, groupingData, aggregateData)};

    EXPECT_TRUE(success);
    EXPECT_EQ(results.at("group1"), 2);
    EXPECT_EQ(results.at("group2"), 4);
}

TEST(OperationTest, ExecuteOperationUnknown)
{
    StreamEater eater(std::cerr);
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    const auto [success, results]{operation::executeOperation(
        operation::Type::UNKNOWN, groupingData, aggregateData)};

    EXPECT_FALSE(success);
    EXPECT_TRUE(results.empty());
}
