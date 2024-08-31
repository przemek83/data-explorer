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

    bool validateQuery(const Dataset& dataset, Query& query) const;

private:
    bool areColumnsValid(const Dataset& dataset) const;

    bool isOperationValid(operation::Type type) const;

    std::string operation_;
    std::string aggregate_;
    std::string grouping_;
};
