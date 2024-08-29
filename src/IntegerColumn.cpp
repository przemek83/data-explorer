#include "IntegerColumn.h"

#include <charconv>
#include <string>

#include "Logger.h"
#include "Operation.h"

Column::ColumnType IntegerColumn::getType() const
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
        Logger().logErr("Cannot convert to int: " + item);
    if (errorCode == std::errc::result_out_of_range)
        Logger().logErr("Value out of range: " + item);

    return false;
}

std::unordered_map<std::string, int> IntegerColumn::performOperation(
    OperationType::Type operationType, const std::vector<int>& data) const
{
    const auto [success, results]{
        Operation<int>::executeOperation(operationType, getData(), data)};

    std::unordered_map<std::string, int> resultsWithStrings;
    for (const auto& [columnId, value] : results)
        resultsWithStrings[std::to_string(columnId)] = value;

    return resultsWithStrings;
}
