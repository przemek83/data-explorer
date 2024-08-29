#pragma once

#include "OperationType.h"

struct Query
{
public:
    OperationType::Type operation_{OperationType::Type::UNKNOWN};
    std::size_t aggregateId_{0};
    std::size_t groupingId_{0};
};
