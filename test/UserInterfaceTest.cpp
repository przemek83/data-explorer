#include <memory>

#include <cpputils/StreamEater.h>
#include <gtest/gtest.h>

#include <src/Dataset.h>
#include <src/UserInterface.h>

#include "FakeLoader.h"

namespace
{
class UserInterfaceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dataset_ = std::make_unique<Dataset>(std::make_unique<FakeLoader>());
        dataset_->init();
    }

    std::unique_ptr<Dataset> dataset_;
    Query query_;
    StreamEater eaterCerr_{std::cerr};
    StreamEater eaterCout_{std::cout};
};
};  // namespace

TEST_F(UserInterfaceTest, GetQueryOperationUnknown)
{
    UserInterface ui("wrong h1 h2");
    EXPECT_FALSE(ui.validateQuery(*dataset_, query_));
}

TEST_F(UserInterfaceTest, GetQueryOperationQuit)
{
    UserInterface ui("quit");
    EXPECT_TRUE(ui.validateQuery(*dataset_, query_));
}

TEST_F(UserInterfaceTest, GetQueryOperationCorrectInput)
{
    UserInterface ui("max h1 h2");
    EXPECT_TRUE(ui.validateQuery(*dataset_, query_));
}

TEST_F(UserInterfaceTest, GetQueryOperationSameColumn)
{
    UserInterface ui("max h1 h1");
    EXPECT_FALSE(ui.validateQuery(*dataset_, query_));
}

TEST_F(UserInterfaceTest, GetQueryOperationWrongAggregating)
{
    UserInterface ui("max wrong h1");
    EXPECT_FALSE(ui.validateQuery(*dataset_, query_));
}

TEST_F(UserInterfaceTest, GetQueryOperationWrongGrouping)
{
    UserInterface ui("max h1 wrong");
    EXPECT_FALSE(ui.validateQuery(*dataset_, query_));
}

TEST_F(UserInterfaceTest, GetQueryOperationWrongAggregatingColumn)
{
    UserInterface ui("max h3 h2");
    EXPECT_FALSE(ui.validateQuery(*dataset_, query_));
}
