#pragma once

#include "Operation.h"

struct Query
{
public:
    operation::Type operation_{operation::Type::UNKNOWN};
    std::size_t aggregateId_{0};
    std::size_t groupingId_{0};
};
