#include "Dataset.h"

#include <algorithm>
#include <cstddef>

Dataset::Dataset(std::unique_ptr<DataLoader> dataLoader)
    : dataLoader_(std::move(dataLoader))
{
}

bool Dataset::init()
{
    return dataLoader_->loadData(headers_, columnTypes_, columns_);
}

std::size_t Dataset::getColumnId(const std::string& name) const
{
    const auto pos{std::find(headers_.cbegin(), headers_.cend(), name)};
    return static_cast<std::size_t>(std::distance(headers_.cbegin(), pos));
}

bool Dataset::isColumnNameValid(const std::string& name) const
{
    const auto it{find(headers_.cbegin(), headers_.cend(), name)};
    return it != headers_.end();
}

bool Dataset::isColumnCanBeUsedForAggregation(const std::string& name) const
{
    const std::size_t id{getColumnId(name)};
    return columnTypes_[id] == Column::ColumnType::INTEGER;
}

std::unordered_map<std::string, int> Dataset::executeQuery(
    const Query query) const
{
    const std::vector<int>& aggregateData{
        columns_[query.aggregateId_]->getData()};
    return columns_[query.groupingId_]->performOperation(query.operation_,
                                                         aggregateData);
}
