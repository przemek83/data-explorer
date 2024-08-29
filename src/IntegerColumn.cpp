#include "IntegerColumn.h"

#include <charconv>
#include <iostream>
#include <ostream>

#include "Operation.h"

Column::ColumnType IntegerColumn::getColumnType() const
{
    return Column::ColumnType::INTEGER;
}

bool IntegerColumn::addItem(const std::string& item)
{
    int value{0};
    const auto [_, errorCode]{
        std::from_chars(item.data(), item.data() + item.size(), value)};
    if (errorCode == std::errc())
    {
        addData(value);
        return true;
    }

    if (errorCode == std::errc::invalid_argument)
        std::cerr << "Cannot convert to int: " << item << std::endl;
    if (errorCode == std::errc::result_out_of_range)
        std::cerr << "Value out of range: " << item << std::endl;

    return false;
}

std::unordered_map<std::string, int> IntegerColumn::performOperation(
    OperationType::Type operationType, const std::vector<int>& data) const
{
    const std::unordered_map<int, int> results{
        Operation<int>::executeOperation(operationType, getData(), data)};

    std::unordered_map<std::string, int> resultsWithStrings;
    for (const auto& [columnId, value] : results)
        resultsWithStrings[std::to_string(columnId)] = value;

    return resultsWithStrings;
}
