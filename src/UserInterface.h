#pragma once

#include <string>

#include "Query.h"

class Dataset;

class UserInterface
{
public:
    explicit UserInterface(const std::string& input);
    virtual ~UserInterface() = default;

    UserInterface& operator=(const UserInterface& other) = delete;
    UserInterface(const UserInterface& other) = delete;

    UserInterface& operator=(UserInterface&& other) = default;
    UserInterface(UserInterface&& other) = default;

    bool getValidatedUserQueryForDataset(const Dataset& dataset,
                                         Query& query) const;

    static void printCommandHelp();

private:
    bool areColumnsValid(const std::string& aggregateColumn,
                         const std::string& groupingColumn,
                         const Dataset& dataset) const;

    std::string operationInputString_{};
    std::string aggregateColumnInputString_{};
    std::string groupingColumnInputString_{};
};
