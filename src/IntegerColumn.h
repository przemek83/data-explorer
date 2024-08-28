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

    inline bool addDataItem(const std::string& dataItem) override
    {
        int value{0};
        const auto [_, errorCode] = std::from_chars(
            dataItem.data(), dataItem.data() + dataItem.size(), value);
        if (errorCode == std::errc())
        {
            data_.push_back(value);
            return true;
        }

        if (errorCode == std::errc::invalid_argument)
            std::cerr << "Cannot convert to int: " << dataItem << std::endl;
        if (errorCode == std::errc::result_out_of_range)
            std::cerr << "Value out of range: " << dataItem << std::endl;

        return false;
    }

    std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const override;

    const std::vector<int>& getData() const;

private:
    std::vector<int> data_;
};
