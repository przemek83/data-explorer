#include "Column.h"

#include <algorithm>
#include <stdexcept>

std::map<Column::ColumnType, std::string> Column::types_{
    {Column::ColumnType::INTEGER, "integer"},
    {Column::ColumnType::STRING, "string"}};

std::string Column::getColumnNameForType(Column::ColumnType type)
{
    return types_[type];
}

Column::ColumnType Column::getColumnTypeForName(const std::string& name)
{
    const auto condition{[&columnName = name](const auto& pair)
                         { return pair.second == columnName; }};
    const auto result{std::find_if(types_.cbegin(), types_.cend(), condition)};

    if (result == types_.cend())
        throw std::logic_error("Unknown column name " + name);

    return result->first;
};