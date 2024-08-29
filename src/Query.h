#pragma once

#include "OperationType.h"

struct Query
{
public:
    OperationType::Type operation{OperationType::Type::UNKNOWN};
    std::size_t aggregateColumnId{0};
    std::size_t groupingColumnId{0};
};
