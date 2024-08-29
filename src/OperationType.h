#pragma once

#include <cstdint>
#include <string>

namespace OperationType
{
enum class Type : uint8_t
{
    AVG = 0,
    MIN,
    MAX,
    QUIT,
    UNKNOWN
};

OperationType::Type getOperationTypeForString(
    const std::string& operationTypeString);

std::string getAvailableOperationsAsString(const std::string& delimiter);
};  // namespace OperationType