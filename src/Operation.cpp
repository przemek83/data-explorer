#include "Operation.h"

#include <algorithm>
#include <cctype>
#include <map>

namespace
{
std::map<std::string, operation::Type, std::less<>> getMapping()
{
    return {{"AVG", operation::Type::AVG},
            {"MIN", operation::Type::MIN},
            {"MAX", operation::Type::MAX},
            {"QUIT", operation::Type::QUIT}};
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
    std::string result;
    for (const auto& [stringPart, _] : getMapping())
    {
        result += stringPart;
        result += delimiter;
    }
    result.pop_back();

    std::transform(result.begin(), result.end(), result.begin(), ::tolower);

    return result;
}
};  // namespace operation
