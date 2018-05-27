#include "Column.h"

std::map<Column::ColumnType, std::string> Column::columnTypeMapping_ =
    {{Column::ColumnType::INTEGER, "integer"},
     {Column::ColumnType::STRING, "string"}};

std::string Column::getColumnNameForType(Column::ColumnType columnType)
{
    return columnTypeMapping_[columnType];
}

Column::ColumnType Column::getColumnTypeForName(std::string columnName)
{
    for (auto& pair : columnTypeMapping_)
    {
        if (pair.second == columnName)
        {
            return pair.first;
        }
    }

    throw std::logic_error("Unknown column name " + columnName);
}
