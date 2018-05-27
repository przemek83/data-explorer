#include <iostream>

#include "StringColumn.h"

StringColumn::StringColumn() :
    data_(std::vector<unsigned int>()), stringToIdMapping_(std::unordered_map<std::string, unsigned int>())
{

}

Column::ColumnType StringColumn::getColumnType() const
{
    return Column::ColumnType::STRING;
}

const std::vector<unsigned int>& StringColumn::getData()
{
    return data_;
}

std::unordered_map<std::string, int>
    StringColumn::performOperation(Operation::OperationType operationType, const std::vector<int>& data)
{
    std::unordered_map<unsigned int, int> indirectResults =
        Operation::executeOperation<unsigned int>(operationType, data_, data);

    std::unordered_map<std::string, int> resultsToReturn;
    for (const auto& item : indirectResults)
    {
        for (const auto& stringMappingItem : stringToIdMapping_)
        {
            if (stringMappingItem.second == item.first)
            {
                resultsToReturn[stringMappingItem.first] = item.second;
            }
        }
    }

    return resultsToReturn;
}
