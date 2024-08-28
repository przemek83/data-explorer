#pragma once

#include <map>
#include <string>
#include <vector>

#include "Operation.h"

class Column
{
public:
    enum class ColumnType : uint8_t
    {
        STRING = 0,
        INTEGER
    };

    Column() = default;

    virtual ~Column() = default;

    Column& operator=(const Column& other) = default;
    Column(const Column& other) = default;

    Column& operator=(Column&& other) = default;
    Column(Column&& other) = default;

    static std::string getColumnNameForType(Column::ColumnType columnType);

    static ColumnType getColumnTypeForName(const std::string& columnName);

    virtual ColumnType getColumnType() const = 0;

    virtual bool addDataItem(const std::string& dataItem) = 0;

    virtual std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const = 0;

private:
    static std::map<ColumnType, std::string> columnTypes_;
};
