#include <gtest/gtest.h>

#include <src/Dataset.h>
#include <src/UserInterface.h>
#include <memory>

#include "FakeLoader.h"

TEST(UserInterface, GetQueryOperationUnknown)
{
    UserInterface userInterface("wrong h1 h2");
    Dataset dataset{std::make_unique<FakeLoader>()};
    dataset.init();

    Query query;
    EXPECT_FALSE(userInterface.getValidatedUserQueryForDataset(dataset, query));
}

TEST(UserInterface, GetQueryOperationQuit)
{
    UserInterface userInterface("quit");
    Dataset dataset{std::make_unique<FakeLoader>()};
    dataset.init();

    Query query;
    EXPECT_TRUE(userInterface.getValidatedUserQueryForDataset(dataset, query));
}

TEST(UserInterface, GetQueryOperationCorrectInput)
{
    UserInterface userInterface("max h1 h2");
    Dataset dataset{std::make_unique<FakeLoader>()};
    dataset.init();

    Query query;
    EXPECT_TRUE(userInterface.getValidatedUserQueryForDataset(dataset, query));
}

TEST(UserInterface, GetQueryOperationSameColumn)
{
    UserInterface userInterface("max h1 h1");
    Dataset dataset{std::make_unique<FakeLoader>()};
    dataset.init();

    Query query;
    EXPECT_FALSE(userInterface.getValidatedUserQueryForDataset(dataset, query));
}

TEST(UserInterface, GetQueryOperationWrongAggregating)
{
    UserInterface userInterface("max wrong h1");
    Dataset dataset{std::make_unique<FakeLoader>()};
    dataset.init();

    Query query;
    EXPECT_FALSE(userInterface.getValidatedUserQueryForDataset(dataset, query));
}

TEST(UserInterface, GetQueryOperationWrongGrouping)
{
    UserInterface userInterface("max h1 wrong");
    Dataset dataset{std::make_unique<FakeLoader>()};
    dataset.init();

    Query query;
    EXPECT_FALSE(userInterface.getValidatedUserQueryForDataset(dataset, query));
}

TEST(UserInterface, GetQueryOperationWrongAggregatingColumn)
{
    UserInterface userInterface("max h3 h2");
    Dataset dataset{std::make_unique<FakeLoader>()};
    dataset.init();

    Query query;
    EXPECT_FALSE(userInterface.getValidatedUserQueryForDataset(dataset, query));
}
