#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Column.h"

class IntegerColumn;
class StringColumn;

class DataLoader
{
public:
    DataLoader() = default;
    DataLoader(const DataLoader& other) = default;
    DataLoader(DataLoader&& other) = default;

    virtual ~DataLoader() = default;

    DataLoader& operator=(const DataLoader& other) = default;
    DataLoader& operator=(DataLoader&& other) = default;

    virtual bool loadData(
        std::vector<std::string>& headers,
        std::vector<Column::ColumnType>& columnTypes,
        std::vector<std::unique_ptr<Column>>& dataColumns) = 0;
};
