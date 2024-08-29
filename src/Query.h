#pragma once

#include "OperationType.h"

struct Query
{
public:
    OperationType operation{OperationType::UNKNOWN};
    std::size_t aggregateColumnId{0};
    std::size_t groupingColumnId{0};
};
