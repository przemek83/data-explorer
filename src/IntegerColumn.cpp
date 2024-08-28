#include "IntegerColumn.h"

IntegerColumn::IntegerColumn(std::vector<int> data) : data_(std::move(data)) {}

Column::ColumnType IntegerColumn::getColumnType() const
{
    return Column::ColumnType::INTEGER;
}

const std::vector<int>& IntegerColumn::getData() { return data_; }

std::unordered_map<std::string, int> IntegerColumn::performOperation(
    Operation::OperationType operationType, const std::vector<int>& data) const
{
    const std::unordered_map<int, int> results =
        Operation::executeOperation<int>(operationType, data_, data);

    std::unordered_map<std::string, int> resultsWithStrings;
    for (const auto& [columnId, value] : results)
        resultsWithStrings[std::to_string(columnId)] = value;

    return resultsWithStrings;
}
