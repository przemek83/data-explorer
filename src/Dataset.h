#pragma once

#include <memory>

#include "DataLoader.h"
#include "Query.h"

class Dataset
{
public:
    explicit Dataset(std::unique_ptr<DataLoader> dataLoader);

    bool init();

    std::size_t getColumnId(const std::string& name) const;

    bool isColumnNameValid(const std::string& name) const;

    bool isColumnCanBeUsedForAggregation(const std::string& name) const;

    std::unordered_map<std::string, int> executeQuery(const Query query) const;

private:
    std::unique_ptr<DataLoader> dataLoader_;

    std::vector<std::string> headers_;

    std::vector<Column::ColumnType> columnTypes_;

    std::vector<std::unique_ptr<Column>> columns_;
};
