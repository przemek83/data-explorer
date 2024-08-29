#pragma once

#include <vector>

#include "Column.h"
#include "OperationType.h"

class IntegerColumn : public Column
{
public:
    using Column::Column;

    ColumnType getColumnType() const override;

    bool addItem(const std::string& item) override;

    std::unordered_map<std::string, int> performOperation(
        OperationType operationType,
        const std::vector<int>& data) const override;
};
