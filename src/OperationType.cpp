#include "OperationType.h"

#include <map>

namespace OperationType
{

const std::map<std::string, OperationType::Type> stringToOperationTypeMapping_{
    {"avg", OperationType::Type::AVG},
    {"min", OperationType::Type::MIN},
    {"max", OperationType::Type::MAX},
    {"quit", OperationType::Type::QUIT}};

OperationType::Type getOperationTypeForString(
    const std::string& operationTypeString)
{
    const auto& findResult =
        stringToOperationTypeMapping_.find(operationTypeString);
    return (findResult != stringToOperationTypeMapping_.end()
                ? findResult->second
                : OperationType::Type::UNKNOWN);
}

std::string getAvailableOperationsAsString(const std::string& delimiter)
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
};  // namespace OperationType