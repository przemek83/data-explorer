#include <sstream>

#include "gtest/gtest.h"

#include <Dataset.h>
#include <FileDataLoader.h>

static const std::string sampleData =
    R"(first_name;age;movie_name;score
string;integer;string;integer
tim;26;inception;8
tim;26;pulp_fiction;8
tamas;44;inception;7
tamas;44;pulp_fiction;4
dave;0;inception;8
dave;0;ender's_game;8)";

TEST(DataExplorer, executeQuery)
{
    std::unique_ptr<std::istringstream> stream =
        std::make_unique<std::istringstream>(sampleData);

    std::unique_ptr<FileDataLoader> loader(
        new FileDataLoader(std::move(stream)));
    Dataset dataset(std::move(loader));

    ASSERT_TRUE(dataset.init());

    std::unordered_map<std::string, int> expected{
        {"tim", 26}, {"tamas", 44}, {"dave", 0}};
    EXPECT_EQ(dataset.executeQuery({Operation::OperationType::MIN, 1, 0}),
              expected);

    expected = {{"inception", 8}, {"pulp_fiction", 8}, {"ender's_game", 8}};
    EXPECT_EQ(dataset.executeQuery({Operation::OperationType::MAX, 3, 2}),
              expected);

    expected = std::unordered_map<std::string, int>{
        {"tim", 8}, {"tamas", 6}, {"dave", 8}};
    EXPECT_EQ(dataset.executeQuery({Operation::OperationType::AVG, 3, 0}),
              expected);
}
