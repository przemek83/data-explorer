#pragma once

#include <vector>

#include "Column.h"
#include "Operation.h"

class IntegerColumn : public Column
{
public:
    using Column::Column;

    bool addItem(const std::string& item) override;

    std::unordered_map<std::string, int> performOperation(
        operation::Type type, const std::vector<int>& data) const override;
};
