#include "UserInterface.h"

#include <algorithm>
#include <cctype>
#include <sstream>

#include <cpputils/Logger.h>

#include "Dataset.h"
#include "Operation.h"

UserInterface::UserInterface(const std::string& input)
{
    std::istringstream iss(input);

    iss >> operation_ >> aggregate_ >> grouping_;
    std::transform(operation_.begin(), operation_.end(), operation_.begin(),
                   ::toupper);
}

bool UserInterface::validateQuery(const Dataset& dataset, Query& query) const
{
    query.operation_ = operation::getOperationTypeForString(operation_);

    if (query.operation_ == operation::Type::QUIT)
        return true;

    if ((!isOperationValid(query.operation_)) || (!areColumnsValid(dataset)))
        return false;

    query.aggregateId_ = dataset.getColumnId(aggregate_);
    query.groupingId_ = dataset.getColumnId(grouping_);

    Log().info("Execute: " + operation_ + " " + aggregate_ + " GROUPED BY " +
               grouping_);

    return true;
}

bool UserInterface::areColumnsValid(const Dataset& dataset) const
{
    bool columnsValid = true;

    if (aggregate_ == grouping_)
    {
        Log().error("Cannot use same column for aggregation and grouping.");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnNameValid(aggregate_)))
    {
        Log().error("Column " + aggregate_ + " not valid");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnNameValid(grouping_)))
    {
        Log().error("Column " + grouping_ + " not valid");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnCanBeUsedForAggregation(aggregate_)))
    {
        Log().error("Cannot aggregate using column " + aggregate_);
        columnsValid = false;
    }

    return columnsValid;
}

bool UserInterface::isOperationValid(operation::Type type) const
{
    if (type == operation::Type::UNKNOWN)
    {
        Log().error("Operation " + operation_ + " is unknown.");
        return false;
    }

    return true;
}
