#include <iostream>
#include <memory>
#include <sstream>
#include <tuple>

#include <cpputils/StreamEater.h>
#include <gtest/gtest.h>

#include <src/FileDataLoader.h>
#include <src/IntegerColumn.h>
#include <src/StringColumn.h>

namespace
{
const std::string sampleData = R"(first_name;age;movie_name;score
string;integer;string;integer
tim;26;inception;8
tim;26;pulp_fiction;8
tamas;44;inception;7
tamas;44;pulp_fiction;4
dave;0;inception;8
dave;0;ender's_game;8)";

std::tuple<std::vector<std::string>, std::vector<Column::ColumnType>,
           std::vector<std::unique_ptr<Column>>>
loadData(std::string stringData)
{
    FileDataLoader loader(std::make_unique<std::istringstream>(stringData));

    std::vector<std::string> headers;
    std::vector<Column::ColumnType> columnTypes;
    std::vector<std::unique_ptr<Column>> dataColumns;

    loader.loadData(headers, columnTypes, dataColumns);

    return {headers, columnTypes, std::move(dataColumns)};
}
}  // namespace

TEST(FileDataLoader, LoadDataSuccess)
{
    FileDataLoader loader{std::make_unique<std::istringstream>(sampleData)};

    std::vector<std::string> headers;
    std::vector<Column::ColumnType> columnTypes;
    std::vector<std::unique_ptr<Column>> dataColumns;

    bool result{loader.loadData(headers, columnTypes, dataColumns)};

    EXPECT_TRUE(result);
}

TEST(FileDataLoader, LoadDataCorruptedTooMuchEntries)
{
    StreamEater eater(std::cerr);
    std::string data{"header1;header2\ninteger;string\n1;hello;f"};
    FileDataLoader loader{std::make_unique<std::istringstream>(data)};

    std::vector<std::string> headers;
    std::vector<Column::ColumnType> columnTypes;
    std::vector<std::unique_ptr<Column>> dataColumns;

    bool result{loader.loadData(headers, columnTypes, dataColumns)};

    EXPECT_FALSE(result);
}

TEST(FileDataLoader, LoadDataCorruptedTooLittleEntries)
{
    StreamEater eater(std::cerr);
    std::string data{"header1;header2\ninteger;string\n1"};
    FileDataLoader loader{std::make_unique<std::istringstream>(data)};

    std::vector<std::string> headers;
    std::vector<Column::ColumnType> columnTypes;
    std::vector<std::unique_ptr<Column>> dataColumns;

    bool result{loader.loadData(headers, columnTypes, dataColumns)};

    EXPECT_FALSE(result);
}

TEST(FileDataLoader, LoadDataSuccessHeaders)
{
    const auto [headers, columnTypes, dataColumns]{loadData(sampleData)};

    EXPECT_EQ(headers.size(), 4);
    EXPECT_EQ(headers[0], "first_name");
    EXPECT_EQ(headers[1], "age");
    EXPECT_EQ(headers[2], "movie_name");
    EXPECT_EQ(headers[3], "score");
}

TEST(FileDataLoader, LoadDataSuccessColumnTypes)
{
    const auto [headers, columnTypes, dataColumns]{loadData(sampleData)};

    EXPECT_EQ(columnTypes.size(), 4);
    EXPECT_EQ(columnTypes[0], Column::ColumnType::STRING);
    EXPECT_EQ(columnTypes[1], Column::ColumnType::INTEGER);
    EXPECT_EQ(columnTypes[2], Column::ColumnType::STRING);
    EXPECT_EQ(columnTypes[3], Column::ColumnType::INTEGER);
}

TEST(FileDataLoader, LoadDataSuccessData)
{
    const auto [headers, columnTypes, dataColumns]{loadData(sampleData)};

    EXPECT_EQ(dataColumns.size(), 4);
}
