#include <memory>
#include "src/Column.h"
#include "src/DataLoader.h"

#include <gtest/gtest.h>

#include <src/Dataset.h>
#include <src/IntegerColumn.h>
#include <src/StringColumn.h>

namespace
{
class FakeLoader : public DataLoader
{
public:
    bool loadData(std::vector<std::string>& headers,
                  std::vector<Column::ColumnType>& columnTypes,
                  std::vector<std::unique_ptr<Column>>& dataColumns) override
    {
        if (!loadDataResult_)
            return false;

        headers = {"h1", "h2", "h3"};
        columnTypes = {Column::ColumnType::INTEGER, Column::ColumnType::INTEGER,
                       Column::ColumnType::STRING};

        dataColumns.push_back(std::make_unique<IntegerColumn>(
            std::vector<int>{1, 2, 3, 11, 12, 13}));
        dataColumns.push_back(std::make_unique<IntegerColumn>(
            std::vector<int>{4, 5, 6, 14, 15, 16}));

        auto stringColumn{std::make_unique<StringColumn>()};
        stringColumn->addDataItem("Entry1");
        stringColumn->addDataItem("Entry2");
        stringColumn->addDataItem("Entry3");
        stringColumn->addDataItem("Entry1");
        stringColumn->addDataItem("Entry2");
        stringColumn->addDataItem("Entry3");
        dataColumns.push_back(std::move(stringColumn));

        return true;
    }

    void setLoadDataResult(bool result) { loadDataResult_ = result; }

private:
    bool loadDataResult_{true};
};

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

    EXPECT_EQ(dataset.getColumnIdForName("h1"), 0);
    EXPECT_EQ(dataset.getColumnIdForName("h2"), 1);
    EXPECT_EQ(dataset.getColumnIdForName("h3"), 2);
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

    EXPECT_TRUE(dataset.isColumnNameCanBeUsedForAggregation("h1"));
    EXPECT_TRUE(dataset.isColumnNameCanBeUsedForAggregation("h2"));
    EXPECT_FALSE(dataset.isColumnNameCanBeUsedForAggregation("h3"));
}

TEST(DatasetTest, ExecuteQueryMax)
{
    Query query{Operation::OperationType::MAX, 0, 2};
    testResults(query, {11, 12, 13});

    query = {Operation::OperationType::MAX, 1, 2};
    testResults(query, {14, 15, 16});
}

TEST(DatasetTest, ExecuteQueryMin)
{
    Query query{Operation::OperationType::MIN, 0, 2};
    testResults(query, {1, 2, 3});

    query = {Operation::OperationType::MIN, 1, 2};
    testResults(query, {4, 5, 6});
}

TEST(DatasetTest, ExecuteQueryAvg)
{
    Query query{Operation::OperationType::AVG, 0, 2};
    testResults(query, {6, 7, 8});

    query = {Operation::OperationType::AVG, 1, 2};
    testResults(query, {9, 10, 11});
}
