#pragma once

#include <charconv>
#include <iostream>
#include <vector>

#include "Column.h"

class IntegerColumn : public Column
{
public:
    explicit IntegerColumn(std::vector<int> data);

    ColumnType getColumnType() const override;

    bool addDataItem(const std::string& item) override;

    std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const override;

    const std::vector<int>& getData() const override;

private:
    std::vector<int> data_;
};
