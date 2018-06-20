#include "Dataset.h"

#include <iostream>
#include <algorithm>

Dataset::Dataset(std::unique_ptr<DataLoader> dataLoader) : dataLoader_(std::move(dataLoader))
{

}

Dataset::~Dataset()
{
    for (Column* column : columns_)
    {
        delete column;
    }
}

bool Dataset::init()
{
    return dataLoader_->loadData(headers_, columnTypes_, columns_);
}

unsigned int Dataset::getColumnIdForName(const std::string& columnName) const
{
    return std::distance(headers_.begin(), std::find(headers_.begin(), headers_.end(), columnName));
}

bool Dataset::isColumnNameValid(const std::string& columnName) const
{
    auto iterator = find (headers_.begin(), headers_.end(), columnName);
    return iterator != headers_.end();
}

bool Dataset::isColumnNameCanBeUsedForAggregation(const std::string& columnName) const
{
    return columnTypes_[getColumnIdForName(columnName)] == Column::ColumnType::INTEGER;
}

std::unordered_map<std::string, int> Dataset::executeQuery(const Query& query) const
{
    const std::vector<int>& aggregateData =
        static_cast<IntegerColumn*>(columns_[query.aggregateColumnId])->getData();
    return columns_[query.groupingColumnId]->performOperation(query.operation, aggregateData);
}
