#include <memory>

#include <cpputils/StreamEater.h>
#include <gtest/gtest.h>

#include <src/Column.h>
#include <src/DataLoader.h>
#include <src/Dataset.h>
#include <src/IntegerColumn.h>
#include <src/StringColumn.h>

#include "FakeLoader.h"

namespace
{
void testResults(Query query, std::vector<int> expected)
{
    Dataset dataset(std::make_unique<FakeLoader>());
    dataset.init();
    auto result{dataset.executeQuery(query)};

    EXPECT_EQ(result["Entry1"], expected[0]);
    EXPECT_EQ(result["Entry2"], expected[1]);
    EXPECT_EQ(result["Entry3"], expected[2]);
}
}  // namespace

TEST(DatasetTest, InitSuccess)
{
    Dataset dataset(std::make_unique<FakeLoader>());
    bool result = dataset.init();

    EXPECT_TRUE(result);
}

TEST(DatasetTest, InitFailure)
{
    auto loader{std::make_unique<FakeLoader>()};
    loader->setLoadDataResult(false);
    Dataset dataset(std::move(loader));
    bool result = dataset.init();

    EXPECT_FALSE(result);
}

TEST(DatasetTest, GetColumnIdForName)
{
    Dataset dataset(std::make_unique<FakeLoader>());
    dataset.init();

    EXPECT_EQ(dataset.getColumnId("h1"), 0);
    EXPECT_EQ(dataset.getColumnId("h2"), 1);
    EXPECT_EQ(dataset.getColumnId("h3"), 2);
}

TEST(DatasetTest, IsColumnNameValid)
{
    Dataset dataset(std::make_unique<FakeLoader>());
    dataset.init();

    EXPECT_TRUE(dataset.isColumnNameValid("h1"));
    EXPECT_TRUE(dataset.isColumnNameValid("h2"));
    EXPECT_TRUE(dataset.isColumnNameValid("h3"));
    EXPECT_FALSE(dataset.isColumnNameValid("non existing"));
}

TEST(DatasetTest, IsColumnNameCanBeUsedForAggregation)
{
    Dataset dataset(std::make_unique<FakeLoader>());
    dataset.init();

    EXPECT_TRUE(dataset.isColumnCanBeUsedForAggregation("h1"));
    EXPECT_TRUE(dataset.isColumnCanBeUsedForAggregation("h2"));
    EXPECT_FALSE(dataset.isColumnCanBeUsedForAggregation("h3"));
}

TEST(DatasetTest, ExecuteQueryMax)
{
    Query query{operation::Type::MAX, 0, 2};
    testResults(query, {11, 12, 13});

    query = {operation::Type::MAX, 1, 2};
    testResults(query, {14, 15, 16});
}

TEST(DatasetTest, ExecuteQueryMin)
{
    Query query{operation::Type::MIN, 0, 2};
    testResults(query, {1, 2, 3});

    query = {operation::Type::MIN, 1, 2};
    testResults(query, {4, 5, 6});
}

TEST(DatasetTest, ExecuteQueryAvg)
{
    Query query{operation::Type::AVG, 0, 2};
    testResults(query, {6, 7, 8});

    query = {operation::Type::AVG, 1, 2};
    testResults(query, {9, 10, 11});
}

TEST(DatasetTest, ExecuteQueryUnknownOperation)
{
    StreamEater eater(std::cerr);
    Dataset dataset(std::make_unique<FakeLoader>());
    dataset.init();

    Query query{operation::Type::UNKNOWN, 0, 2};
    EXPECT_TRUE(dataset.executeQuery(query).empty());
}
