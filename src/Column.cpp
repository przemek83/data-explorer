#include "Column.h"

#include <algorithm>
#include <stdexcept>

std::map<Column::ColumnType, std::string> Column::columnTypes_{
    {Column::ColumnType::INTEGER, "integer"},
    {Column::ColumnType::STRING, "string"}};

std::string Column::getColumnNameForType(Column::ColumnType columnType)
{
    return columnTypes_[columnType];
}

Column::ColumnType Column::getColumnTypeForName(const std::string& columnName)
{
    const auto condition{[&name = columnName](const auto& pair)
                         { return pair.second == name; }};
    const auto result{
        std::find_if(columnTypes_.cbegin(), columnTypes_.cend(), condition)};

    if (result == columnTypes_.cend())
        throw std::logic_error("Unknown column name " + columnName);

    return result->first;
};