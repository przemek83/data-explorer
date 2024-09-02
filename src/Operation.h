#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <cpputils/Logger.h>

namespace operation
{
enum class Type : uint8_t
{
    AVG = 0,
    MIN,
    MAX,
    QUIT,
    UNKNOWN
};

operation::Type getOperationTypeForString(
    const std::string& operationTypeString);

std::string getAvailableOperationsAsString(const std::string& delimiter);

template <typename T, class Func>
std::unordered_map<T, int> computeExtremum(
    const std::vector<T>& groupingData, const std::vector<int>& aggregateData,
    Func func)
{
    std::unordered_map<T, int> results;
    const std::size_t dataSize{groupingData.size()};
    for (unsigned int i = 0; i < dataSize; ++i)
    {
        const auto& element = results.find(groupingData[i]);
        if (element == results.end())
        {
            results[groupingData[i]] = aggregateData[i];
        }
        else
        {
            if (func(element->second, aggregateData[i]))
            {
                element->second = aggregateData[i];
            }
        }
    }

    return results;
}

template <typename T>
std::unordered_map<T, int> computeAverage(const std::vector<T>& groupingData,
                                          const std::vector<int>& aggregateData)
{
    std::unordered_map<T, std::pair<long long int, int>> indirectResults;
    std::size_t groupingDataSize{groupingData.size()};
    for (std::size_t i{0}; i < groupingDataSize; ++i)
    {
        auto& pair = indirectResults[groupingData[i]];
        pair.first += aggregateData[i];
        ++pair.second;
    }

    std::unordered_map<T, int> results;
    for (const auto& item : indirectResults)
    {
        const float avg{static_cast<float>(item.second.first) /
                        static_cast<float>(item.second.second)};

        results[item.first] = static_cast<int>(std::round(avg));
    }

    return results;
}

template <typename T>
std::pair<bool, std::unordered_map<T, int>> executeOperation(
    operation::Type type, const std::vector<T>& groupingData,
    const std::vector<int>& aggregateData)
{
    std::unordered_map<T, int> results;

    switch (type)
    {
        case operation::Type::AVG:
        {
            results = computeAverage(groupingData, aggregateData);
            break;
        }

        case operation::Type::MIN:
        {
            results = computeExtremum(groupingData, aggregateData,
                                      [](int a, int b) { return a > b; });
            break;
        }

        case operation::Type::MAX:
        {
            results = computeExtremum(groupingData, aggregateData,
                                      [](int a, int b) { return a <= b; });
            break;
        }

        default:
        {
            Logger().logErr("Unknown Operation Type " +
                            std::to_string(static_cast<int>(type)));
            return {false, {}};
        }
    }
    return {true, results};
}

};  // namespace operation
