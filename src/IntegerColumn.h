#pragma once

#include <iostream>
#include <vector>

#include "Column.h"

class IntegerColumn : public Column
{
public:
    explicit IntegerColumn(std::vector<int> data);

    ~IntegerColumn() override = default;

    IntegerColumn& operator=(const IntegerColumn& other) = delete;
    IntegerColumn(const IntegerColumn& other) = delete;

    IntegerColumn& operator=(IntegerColumn&& other) = default;
    IntegerColumn(IntegerColumn&& other) = default;

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
        }
        catch (std::out_of_range& e)
        {
            std::cerr << "Value out of range: " << e.what() << std::endl;
        }

        data_.push_back(value);
    }

    std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) override;

    const std::vector<int>& getData();

private:
    std::vector<int> data_;
};
