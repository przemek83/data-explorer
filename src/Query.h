#pragma once

#include "Operation.h"

struct Query
{
public:
    Operation::OperationType operation{Operation::OperationType::UNKNOWN};
    std::size_t aggregateColumnId{0};
    std::size_t groupingColumnId{0};
};
