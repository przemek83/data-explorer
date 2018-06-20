#include "IntegerColumn.h"

#include <iostream>

IntegerColumn::IntegerColumn(std::vector<int> data) : data_(data)
{

}

Column::ColumnType IntegerColumn::getColumnType() const
{
    return Column::ColumnType::INTEGER;
}

const std::vector<int>& IntegerColumn::getData()
{
    return data_;
}

std::unordered_map<std::string, int>
    IntegerColumn::performOperation(Operation::OperationType operationType, const std::vector<int>& data)
{
    const std::unordered_map<int, int> results = Operation::executeOperation<int>(operationType, data_, data);

    std::unordered_map<std::string, int> resultsWithStrings;
    for (const auto& pair : results)
    {
        resultsWithStrings[std::to_string(pair.first)] = pair.second;
    }

    return resultsWithStrings;
}

