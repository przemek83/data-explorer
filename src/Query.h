#ifndef QUERY_H
#define QUERY_H

#include "Operation.h"

struct Query
{
public:
    Operation::OperationType operation{Operation::OperationType::UNKNOWN};
    unsigned int aggregateColumnId{0};
    unsigned int groupingColumnId{0};
};

#endif  // QUERY_H
