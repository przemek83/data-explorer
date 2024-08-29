#include "OperationType.h"

#include <map>

namespace
{
std::map<std::string, OperationType::Type> getMapping()
{
    return {{"avg", OperationType::Type::AVG},
            {"min", OperationType::Type::MIN},
            {"max", OperationType::Type::MAX},
            {"quit", OperationType::Type::QUIT}};
}
}  // namespace

namespace OperationType
{
OperationType::Type getOperationTypeForString(
    const std::string& operationTypeString)
{
    const auto mapping{getMapping()};
    const auto& findResult{mapping.find(operationTypeString)};

    if (findResult != mapping.end())
        return findResult->second;
    else
        return OperationType::Type::UNKNOWN;
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
};  // namespace OperationType
