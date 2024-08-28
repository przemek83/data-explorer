#pragma once

#include <memory>
#include <vector>

#include "Column.h"

class StringColumn : public Column
{
public:
    ColumnType getColumnType() const override;

    bool addDataItem(const std::string& dataItem) override;

    const std::vector<unsigned int>& getData() const;

    std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const override;

private:
    std::string getColumnNameUsingId(int id) const;

    std::vector<unsigned int> data_{};

    std::unordered_map<std::string, unsigned int> stringToIdMapping_{};

    unsigned int currentIndex_{0};
};
