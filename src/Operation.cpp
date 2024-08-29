#include "Operation.h"

const std::map<std::string, OperationType>
    Operation::stringToOperationTypeMapping_{{"avg", OperationType::AVG},
                                             {"min", OperationType::MIN},
                                             {"max", OperationType::MAX},
                                             {"quit", OperationType::QUIT}};

OperationType Operation::getOperationTypeForString(
    const std::string& operationTypeString)
{
    const auto& findResult =
        stringToOperationTypeMapping_.find(operationTypeString);
    return (findResult != stringToOperationTypeMapping_.end()
                ? findResult->second
                : OperationType::UNKNOWN);
}

std::string Operation::getAvailableOperationsAsString(
    const std::string& delimiter)
{
    std::string resultString;
    for (const auto& [stringPart, _] : stringToOperationTypeMapping_)
    {
        resultString += stringPart;
        resultString += delimiter;
    }
    resultString.pop_back();

    return resultString;
}
