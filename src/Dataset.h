#pragma once

#include <memory>

#include "DataLoader.h"
#include "Query.h"

class Dataset final
{
public:
    explicit Dataset(std::unique_ptr<DataLoader> dataLoader);

    ~Dataset() = default;

    Dataset& operator=(const Dataset& other) = delete;
    Dataset(const Dataset& other) = delete;

    Dataset& operator=(Dataset&& other) = default;
    Dataset(Dataset&& other) = default;

    bool init();

    unsigned int getColumnIdForName(const std::string& columnName) const;

    bool isColumnNameValid(const std::string& columnName) const;

    bool isColumnNameCanBeUsedForAggregation(
        const std::string& columnName) const;

    std::unordered_map<std::string, int> executeQuery(const Query query) const;

private:
    std::unique_ptr<DataLoader> dataLoader_;

    std::vector<std::string> headers_;

    std::vector<Column::ColumnType> columnTypes_;

    std::vector<std::unique_ptr<Column>> columns_;
};
