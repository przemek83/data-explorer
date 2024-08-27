#pragma once

#include <iostream>
#include <vector>

#include "Column.h"

class IntegerColumn : public Column
{
public:
    explicit IntegerColumn(std::vector<int> data);

    ColumnType getColumnType() const override;

    inline void addDataItem(const std::string& dataItem) override
    {
        int value = 0;
        try
        {
            value = std::stoi(dataItem);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << "Cannot convert to int: " << e.what() << std::endl;
            return;
        }
        catch (std::out_of_range& e)
        {
            std::cerr << "Value out of range: " << e.what() << std::endl;
            return;
        }

        data_.push_back(value);
    }

    std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const override;

    const std::vector<int>& getData();

private:
    std::vector<int> data_;
};
