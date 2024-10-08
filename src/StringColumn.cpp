#include "StringColumn.h"

#include <algorithm>

#include "Operation.h"

StringColumn::StringColumn() : Column({}) {}

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
    operation::Type type, const std::vector<int>& data) const
{
    const auto [success, indirectResults]{
        operation::executeOperation(type, getData(), data)};

    std::unordered_map<std::string, int> resultsToReturn;
    for (const auto& [columnId, value] : indirectResults)
        resultsToReturn[getColumnNameUsingId(columnId)] = value;

    return resultsToReturn;
}

std::string StringColumn::getColumnNameUsingId(int id) const
{
    const auto condition{[&columnId = id](const auto& pair)
                         { return pair.second == columnId; }};
    const auto result{std::find_if(stringToIdMapping_.cbegin(),
                                   stringToIdMapping_.cend(), condition)};

    return result->first;
}
