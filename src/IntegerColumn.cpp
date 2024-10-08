#include "IntegerColumn.h"

#include <charconv>
#include <string>

#include <cpputils/Logger.h>

#include "Operation.h"

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
        Log().error("Cannot convert to int: " + item);
    if (errorCode == std::errc::result_out_of_range)
        Log().error("Value out of range: " + item);

    return false;
}

std::unordered_map<std::string, int> IntegerColumn::performOperation(
    operation::Type type, const std::vector<int>& data) const
{
    const auto [success,
                results]{operation::executeOperation(type, getData(), data)};

    std::unordered_map<std::string, int> resultsWithStrings;
    for (const auto& [columnId, value] : results)
        resultsWithStrings[std::to_string(columnId)] = value;

    return resultsWithStrings;
}
