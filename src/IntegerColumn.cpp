#include "IntegerColumn.h"

IntegerColumn::IntegerColumn(std::vector<int> data) : data_(std::move(data)) {}

Column::ColumnType IntegerColumn::getColumnType() const
{
    return Column::ColumnType::INTEGER;
}

bool IntegerColumn::addDataItem(const std::string& item)
{
    int value{0};
    const auto [_, errorCode]{
        std::from_chars(item.data(), item.data() + item.size(), value)};
    if (errorCode == std::errc())
    {
        data_.push_back(value);
        return true;
    }

    if (errorCode == std::errc::invalid_argument)
        std::cerr << "Cannot convert to int: " << item << std::endl;
    if (errorCode == std::errc::result_out_of_range)
        std::cerr << "Value out of range: " << item << std::endl;

    return false;
}

const std::vector<int>& IntegerColumn::getData() const { return data_; }

std::unordered_map<std::string, int> IntegerColumn::performOperation(
    Operation::OperationType operationType, const std::vector<int>& data) const
{
    const std::unordered_map<int, int> results{
        Operation::executeOperation<int>(operationType, data_, data)};

    std::unordered_map<std::string, int> resultsWithStrings;
    for (const auto& [columnId, value] : results)
        resultsWithStrings[std::to_string(columnId)] = value;

    return resultsWithStrings;
}
