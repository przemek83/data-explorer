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
    if (query.operation_ == operation::Type::UNKNOWN)
    {
        Logger().logErr("Operation " + operationInputString_ + " is unknown.");
        return false;
    }

    if (query.operation_ == operation::Type::QUIT)
    {
        return true;
    }

    if (!areColumnsValid(aggregateColumnInputString_,
                         groupingColumnInputString_, dataset))
    {
        return false;
    }

    query.aggregateId_ = dataset.getColumnId(aggregateColumnInputString_);
    query.groupingId_ = dataset.getColumnId(groupingColumnInputString_);

    Logger().logMsg("Execute: " + operationInputString_ + " " +
                    aggregateColumnInputString_ + " GROUPED BY " +
                    groupingColumnInputString_);

    return true;
}

bool UserInterface::areColumnsValid(const std::string& aggregateColumn,
                                    const std::string& groupingColumn,
                                    const Dataset& dataset) const
{
    bool columnsValid = true;

    if (aggregateColumn == groupingColumn)
    {
        Logger().logErr("Cannot use same column for aggregation and grouping.");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnNameValid(aggregateColumn)))
    {
        Logger().logErr("Column " + aggregateColumn + " not valid");
        columnsValid = false;
    }

    if (columnsValid && (!dataset.isColumnNameValid(groupingColumn)))
    {
        Logger().logErr("Column " + groupingColumn + " not valid");
        columnsValid = false;
    }

    if (columnsValid &&
        (!dataset.isColumnCanBeUsedForAggregation(aggregateColumn)))
    {
        Logger().logErr("Cannot aggregate using column " + aggregateColumn);
        columnsValid = false;
    }

    return columnsValid;
}
