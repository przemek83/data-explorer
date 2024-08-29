#pragma once

#include <vector>

#include "Column.h"
#include "OperationType.h"

class IntegerColumn : public Column
{
public:
    using Column::Column;

    bool addItem(const std::string& item) override;

    std::unordered_map<std::string, int> performOperation(
        operationType::Type type, const std::vector<int>& data) const override;
};
