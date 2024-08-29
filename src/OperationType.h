#pragma once

#include <cstdint>

enum class OperationType : uint8_t
{
    AVG = 0,
    MIN,
    MAX,
    QUIT,
    UNKNOWN
};
