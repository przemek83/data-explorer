#include "Operation.h"

const std::map<std::string, Operation::OperationType> Operation::stringToOperationTypeMapping_ =
    {{"avg", Operation::OperationType::AVG},
    {"min", Operation::OperationType::MIN},
    {"max", Operation::OperationType::MAX},
    {"test", Operation::OperationType::TEST},
    {"quit", Operation::OperationType::QUIT}};

Operation::OperationType Operation::getOperationTypeForString(const std::string& operationTypeString)
{
    const auto& findResult = stringToOperationTypeMapping_.find(operationTypeString);
    return (findResult != stringToOperationTypeMapping_.end() ? findResult->second : OperationType::UNKNOWN);
}

std::string Operation::getAvailableOperationsAsString(const std::string& delimiter)
{
    std::string resultString;
    for (const auto& item : stringToOperationTypeMapping_)
    {
        resultString += item.first;
        resultString += delimiter;
    }
    resultString.pop_back();

    return resultString;
}
