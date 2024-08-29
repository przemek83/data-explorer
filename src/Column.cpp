#include "Column.h"

#include <algorithm>

#include "Logger.h"

std::map<Column::ColumnType, std::string> Column::types_{
    {Column::ColumnType::INTEGER, "integer"},
    {Column::ColumnType::STRING, "string"}};

Column::Column(std::vector<int> data) : data_{std::move(data)} {}

std::string Column::getColumnName(Column::ColumnType type)
{
    return types_[type];
}

std::pair<bool, Column::ColumnType> Column::getColumnType(
    const std::string& name)
{
    const auto condition{[&columnName = name](const auto& pair)
                         { return pair.second == columnName; }};

    if (const auto it{std::find_if(types_.cbegin(), types_.cend(), condition)};
        it != types_.cend())
        return {true, it->first};

    Logger().logMsg("Cannot find column " + name);

    return {false, {}};
};

const std::vector<int>& Column::getData() const { return data_; };

void Column::addData(int data) { data_.push_back(data); }
