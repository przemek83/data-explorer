#include "UserInterface.h"

#include <sstream>
#include <algorithm>

#include "Dataset.h"
#include "Operation.h"

UserInterface::UserInterface()
{
    std::string inputLine;
    getline(std::cin, inputLine);

    std::istringstream iss(inputLine);

    iss >> operationInputString_ >> aggregateColumnInputString_ >> groupingColumnInputString_;
    std::transform(operationInputString_.begin(),
                   operationInputString_.end(),
                   operationInputString_.begin(),
                   ::tolower);
}

bool UserInterface::getValidatedUserQueryForDataset(const Dataset& dataset, Query& query) const
{
    query.operation = Operation::getOperationTypeForString(operationInputString_);
    if (query.operation == Operation::OperationType::UNKNOWN)
    {
        std::cerr << "Operation " << operationInputString_ << " is unknown." << std::endl;
        return false;
    }

    if (query.operation == Operation::OperationType::QUIT)
    {
        return true;
    }

    if (query.operation == Operation::OperationType::TEST)
    {
        return true;
    }

    if (!areColumnsValid(aggregateColumnInputString_, groupingColumnInputString_, dataset))
    {
        return false;
    }

    query.aggregateColumnId = dataset.getColumnIdForName(aggregateColumnInputString_);
    query.groupingColumnId = dataset.getColumnIdForName(groupingColumnInputString_);

    std:: cout << "Execute: " << operationInputString_ << " " << aggregateColumnInputString_ <<
        " GROUPED BY " << groupingColumnInputString_ << std::endl;

    return true;
}

bool UserInterface::areColumnsValid(const std::string& aggregateColumn,
                                    const std::string& groupingColumn,
                                    const Dataset& dataset) const
{
    bool columnsValid = true;

    if (aggregateColumn == groupingColumn)
    {
        std::cerr << "Cannot use same column for aggregation and grouping." << std::endl;
        columnsValid = false;
    }

    if (columnsValid && !dataset.isColumnNameValid(aggregateColumn))
    {
        std::cerr << "Column " << aggregateColumn << " not valid" << std::endl;
        columnsValid = false;
    }

    if (columnsValid && !dataset.isColumnNameValid(groupingColumn))
    {
        std::cerr << "Column " << groupingColumn << " not valid" << std::endl;
        columnsValid = false;
    }

    if (columnsValid && !dataset.isColumnNameCanBeUsedForAggregation(aggregateColumn))
    {
        std::cerr << "Cannot aggregate using column " << aggregateColumn << std::endl;
        columnsValid = false;
    }

    return columnsValid;
}

void UserInterface::printCommandHelp()
{
    std::stringstream stringStream;
    stringStream << "Usage:" << std::endl;
    stringStream << "<operation> <aggregation> <grouping>" << std::endl;
    stringStream << " operation = {" + Operation::getAvailableOperationsAsString("|") + "}" << std::endl;
    stringStream << " aggregation = column which will be used for aggreagation (numerical only)" << std::endl;
    stringStream << " grouping = column which will be used for grouping" << std::endl;
    std::cout << stringStream.str() << std::endl;
}

