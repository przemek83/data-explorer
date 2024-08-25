#include "Dataset.h"

#include <algorithm>

Dataset::Dataset(std::unique_ptr<DataLoader> dataLoader)
    : dataLoader_(std::move(dataLoader))
{
}

bool Dataset::init()
{
    return dataLoader_->loadData(headers_, columnTypes_, columns_);
}

unsigned int Dataset::getColumnIdForName(const std::string& columnName) const
{
    const auto position =
        std::find(headers_.begin(), headers_.end(), columnName);
    return std::abs(std::distance(headers_.begin(), position));
}

bool Dataset::isColumnNameValid(const std::string& columnName) const
{
    auto iterator = find(headers_.begin(), headers_.end(), columnName);
    return iterator != headers_.end();
}

bool Dataset::isColumnNameCanBeUsedForAggregation(
    const std::string& columnName) const
{
    return columnTypes_[getColumnIdForName(columnName)] ==
           Column::ColumnType::INTEGER;
}

std::unordered_map<std::string, int> Dataset::executeQuery(
    const Query query) const
{
    const std::vector<int>& aggregateData =
        dynamic_cast<IntegerColumn*>(columns_[query.aggregateColumnId].get())
            ->getData();
    return columns_[query.groupingColumnId]->performOperation(query.operation,
                                                              aggregateData);
}
