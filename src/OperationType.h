#pragma once

#include <cstdint>
#include <string>

namespace operationType
{
enum class Type : uint8_t
{
    AVG = 0,
    MIN,
    MAX,
    QUIT,
    UNKNOWN
};

operationType::Type getOperationTypeForString(
    const std::string& operationTypeString);

std::string getAvailableOperationsAsString(const std::string& delimiter);
};  // namespace operationType
