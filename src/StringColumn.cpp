#include "StringColumn.h"

Column::ColumnType StringColumn::getColumnType() const
{
    return Column::ColumnType::STRING;
}

const std::vector<unsigned int>& StringColumn::getData() const { return data_; }

std::unordered_map<std::string, int> StringColumn::performOperation(
    Operation::OperationType operationType, const std::vector<int>& data) const
{
    std::unordered_map<unsigned int, int> indirectResults =
        Operation::executeOperation<unsigned int>(operationType, data_, data);

    std::unordered_map<std::string, int> resultsToReturn;
    for (const auto& [columnId, value] : indirectResults)
        resultsToReturn[getColumnNameUsingId(columnId)] = value;

    return resultsToReturn;
}

std::string StringColumn::getColumnNameUsingId(int columnId) const
{
    const auto condition{[&id = columnId](const auto& pair)
                         { return pair.second == id; }};
    const auto result{std::find_if(stringToIdMapping_.cbegin(),
                                   stringToIdMapping_.cend(), condition)};

    return result->first;
}