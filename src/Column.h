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

    explicit Column(std::vector<int> data);

    virtual ~Column() = default;

    Column& operator=(const Column& other) = default;
    Column(const Column& other) = default;

    Column& operator=(Column&& other) = default;
    Column(Column&& other) = default;

    static std::string getColumnName(Column::ColumnType type);

    static std::pair<bool, Column::ColumnType> getColumnType(
        const std::string& name);

    virtual ColumnType getColumnType() const = 0;

    virtual bool addItem(const std::string& item) = 0;

    virtual std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const = 0;

    const std::vector<int>& getData() const;

protected:
    void addData(int data);

private:
    static std::map<ColumnType, std::string> types_;

    std::vector<int> data_;
};
