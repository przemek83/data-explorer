#pragma once

#include <vector>

#include "Column.h"
#include "OperationType.h"

class StringColumn : public Column
{
public:
    StringColumn();

    ColumnType getColumnType() const override;

    bool addItem(const std::string& item) override;

    std::unordered_map<std::string, int> performOperation(
        OperationType operationType,
        const std::vector<int>& data) const override;

private:
    std::string getColumnNameUsingId(int id) const;

    std::unordered_map<std::string, int> stringToIdMapping_;

    int currentIndex_{0};
};
