#include "StringColumn.h"

#include <algorithm>

#include "Operation.h"

StringColumn::StringColumn() : Column({}) {}

Column::ColumnType StringColumn::getColumnType() const
{
    return Column::ColumnType::STRING;
}

bool StringColumn::addItem(const std::string& item)
{
    if (auto element{stringToIdMapping_.find(item)};
        element != stringToIdMapping_.end())
    {
        addData(element->second);
    }
    else
    {
        stringToIdMapping_[item] = ++currentIndex_;
        addData(currentIndex_);
    }
    return true;
}

std::unordered_map<std::string, int> StringColumn::performOperation(
    OperationType operationType, const std::vector<int>& data) const
{
    std::unordered_map<int, int> indirectResults{
        Operation::executeOperation<int>(operationType, getData(), data)};

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