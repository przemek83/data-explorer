#include "UserInterface.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "Dataset.h"
#include "Logger.h"
#include "Operation.h"

UserInterface::UserInterface()
{
    std::string inputLine;
    getline(std::cin, inputLine);

    std::istringstream iss(inputLine);

    iss >> operationInputString_ >> aggregateColumnInputString_ >>
        groupingColumnInputString_;
    std::transform(operationInputString_.begin(), operationInputString_.end(),
                   operationInputString_.begin(), ::tolower);
}

bool UserInterface::getValidatedUserQueryForDataset(const Dataset& dataset,
                                                    Query& query) const
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

void UserInterface::printCommandHelp()
{
    std::stringstream stringStream(std::ios_base::out);
    stringStream << "Usage:\n";
    stringStream << "<operation> <aggregation> <grouping>\n";
    stringStream << " operation = {" +
                        operation::getAvailableOperationsAsString("|") + "}\n";
    stringStream << " aggregation = column which will be used for aggreagation "
                    "(numerical only)\n";
    stringStream << " grouping = column which will be used for grouping\n";
    Logger().logMsg(stringStream.str());
}
