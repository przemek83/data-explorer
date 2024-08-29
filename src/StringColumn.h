#pragma once

#include <vector>

#include "Column.h"

class StringColumn : public Column
{
public:
    ColumnType getColumnType() const override;

    bool addDataItem(const std::string& item) override;

    std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const override;

    const std::vector<int>& getData() const override;

private:
    std::string getColumnNameUsingId(int id) const;

    std::vector<int> data_;

    std::unordered_map<std::string, int> stringToIdMapping_;

    int currentIndex_{0};
};
