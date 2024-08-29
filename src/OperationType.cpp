#include "OperationType.h"

#include <map>

namespace
{
std::map<std::string, operationType::Type> getMapping()
{
    return {{"avg", operationType::Type::AVG},
            {"min", operationType::Type::MIN},
            {"max", operationType::Type::MAX},
            {"quit", operationType::Type::QUIT}};
}
}  // namespace

namespace operationType
{
operationType::Type getOperationTypeForString(
    const std::string& operationTypeString)
{
    const auto mapping{getMapping()};
    const auto& findResult{mapping.find(operationTypeString)};

    if (findResult != mapping.end())
        return findResult->second;
    else
        return operationType::Type::UNKNOWN;
}

std::string getAvailableOperationsAsString(const std::string& delimiter)
{
    std::string resultString;
    for (const auto& [stringPart, _] : getMapping())
    {
        resultString += stringPart;
        resultString += delimiter;
    }
    resultString.pop_back();

    return resultString;
}
};  // namespace operationType
