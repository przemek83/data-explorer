#include "Column.h"

#include <algorithm>

#include "Logger.h"

Column::Column(std::vector<int> data) : data_{std::move(data)} {}

std::pair<bool, Column::ColumnType> Column::getColumnType(
    const std::string& name)
{
    const auto condition{[&columnName = name](const auto& pair)
                         { return pair.second == columnName; }};

    const auto types{getTypes()};
    if (const auto it{std::find_if(types.cbegin(), types.cend(), condition)};
        it != types.cend())
        return {true, it->first};

    Logger().logMsg("Cannot find column " + name);

    return {false, {}};
};

const std::vector<int>& Column::getData() const { return data_; };

void Column::addData(int data) { data_.push_back(data); }

std::map<Column::ColumnType, std::string> Column::getTypes()
{
    return {{Column::ColumnType::INTEGER, "integer"},
            {Column::ColumnType::STRING, "string"}};
}
