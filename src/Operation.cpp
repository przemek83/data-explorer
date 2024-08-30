#include "Operation.h"

#include <map>

namespace
{
std::map<std::string, operation::Type, std::less<>> getMapping()
{
    return {{"avg", operation::Type::AVG},
            {"min", operation::Type::MIN},
            {"max", operation::Type::MAX},
            {"quit", operation::Type::QUIT}};
}
}  // namespace

namespace operation
{
operation::Type getOperationTypeForString(
    const std::string& operationTypeString)
{
    const auto mapping{getMapping()};
    const auto& findResult{mapping.find(operationTypeString)};

    if (findResult != mapping.end())
        return findResult->second;
    else
        return Type::UNKNOWN;
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
};  // namespace operation
