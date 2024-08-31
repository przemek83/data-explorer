#include "UserInterface.h"

#include <algorithm>
#include <sstream>

#include "Dataset.h"
#include "Logger.h"
#include "Operation.h"

UserInterface::UserInterface(const std::string& input)
{
    std::istringstream iss(input);

    iss >> operationInputString_ >> aggregateColumnInputString_ >>
        groupingColumnInputString_;
    std::transform(operationInputString_.begin(), operationInputString_.end(),
                   operationInputString_.begin(), ::tolower);
}

bool UserInterface::validateQuery(const Dataset& dataset, Query& query) const
{
    query.operation_ =
        operation::getOperationTypeForString(operationInputString_);

    if (query.operation_ == operation::Type::QUIT)
        return true;

    if ((!isOperationValid(query.operation_)) || (!areColumnsValid(dataset)))
        return false;

    query.aggregateId_ = dataset.getColumnId(aggregateColumnInputString_);
    query.groupingId_ = dataset.getColumnId(groupingColumnInputString_);

    Logger().logMsg("Execute: " + operationInputString_ + " " +
                    aggregateColumnInputString_ + " GROUPED BY " +
                    groupingColumnInputString_);

    return true;
}

bool UserInterface::areColumnsValid(const Dataset& dataset) const
{
    const std::string& aggregate{aggregateColumnInputString_};
    const std::string& grouping{groupingColumnInputString_};

    bool columnsValid = true;

    if (aggregate == grouping)
    {
        Logger().logErr("Cannot use same column for aggregation and grouping.");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnNameValid(aggregate)))
    {
        Logger().logErr("Column " + aggregate + " not valid");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnNameValid(grouping)))
    {
        Logger().logErr("Column " + grouping + " not valid");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnCanBeUsedForAggregation(aggregate)))
    {
        Logger().logErr("Cannot aggregate using column " + aggregate);
        columnsValid = false;
    }

    return columnsValid;
}

bool UserInterface::isOperationValid(operation::Type type) const
{
    if (type == operation::Type::UNKNOWN)
    {
        Logger().logErr("Operation " + operationInputString_ + " is unknown.");
        return false;
    }

    return true;
}
