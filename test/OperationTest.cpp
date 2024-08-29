#include <gtest/gtest.h>

#include <src/Operation.h>

TEST(OperationTest, GetOperationTypeForString)
{
    EXPECT_EQ(Operation::getOperationTypeForString("avg"), OperationType::AVG);
    EXPECT_EQ(Operation::getOperationTypeForString("min"), OperationType::MIN);
    EXPECT_EQ(Operation::getOperationTypeForString("max"), OperationType::MAX);
    EXPECT_EQ(Operation::getOperationTypeForString("quit"),
              OperationType::QUIT);
    EXPECT_EQ(Operation::getOperationTypeForString("unknown"),
              OperationType::UNKNOWN);
}

TEST(OperationTest, GetAvailableOperationsAsString)
{
    const std::string expected{"avg,max,min,quit"};
    EXPECT_EQ(Operation::getAvailableOperationsAsString(","), expected);
}

TEST(OperationTest, ExecuteOperationAverage)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 3, 5, 7}};

    auto result{Operation::executeOperation(OperationType::AVG, groupingData,
                                            aggregateData)};

    EXPECT_EQ(result["group1"], 2);
    EXPECT_EQ(result["group2"], 6);
}

TEST(OperationTest, ExecuteOperationMin)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    auto result{Operation::executeOperation(OperationType::MIN, groupingData,
                                            aggregateData)};

    EXPECT_EQ(result["group1"], 1);
    EXPECT_EQ(result["group2"], 3);
}

TEST(OperationTest, ExecuteOperationMax)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    auto result{Operation::executeOperation(OperationType::MAX, groupingData,
                                            aggregateData)};

    EXPECT_EQ(result["group1"], 2);
    EXPECT_EQ(result["group2"], 4);
}

TEST(OperationTest, ExecuteOperationUnknown)
{
    std::vector<std::string> groupingData{
        {"group1", "group1", "group2", "group2"}};
    std::vector<int> aggregateData{{1, 2, 3, 4}};

    EXPECT_THROW(Operation::executeOperation(OperationType::UNKNOWN,
                                             groupingData, aggregateData),
                 std::logic_error);
}
