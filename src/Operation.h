#pragma once

#include <cmath>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "OperationType.h"

template <typename T>
class Operation
{
public:
    Operation() = delete;
    ~Operation() = delete;

    static std::unordered_map<T, int> executeOperation(
        OperationType::Type operationType, const std::vector<T>& groupingData,
        const std::vector<int>& aggregateData)
    {
        std::unordered_map<T, int> results;

        switch (operationType)
        {
            case OperationType::Type::AVG:
            {
                results = computeAverage(groupingData, aggregateData);
                break;
            }

            case OperationType::Type::MIN:
            {
                results = computeExtremum(groupingData, aggregateData,
                                          [](int a, int b) { return a > b; });
                break;
            }

            case OperationType::Type::MAX:
            {
                results = computeExtremum(groupingData, aggregateData,
                                          [](int a, int b) { return a <= b; });
                break;
            }

            default:
            {
                throw std::logic_error(
                    "Unknown Operation Type " +
                    std::to_string(static_cast<int>(operationType)));
            }
        }
        return results;
    }

private:
    template <class Func>
    static std::unordered_map<T, int> computeExtremum(
        const std::vector<T>& groupingData,
        const std::vector<int>& aggregateData, Func func)
    {
        std::unordered_map<T, int> results;
        for (unsigned int i = 0; i < groupingData.size(); ++i)
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

    static std::unordered_map<T, int> computeAverage(
        const std::vector<T>& groupingData,
        const std::vector<int>& aggregateData)
    {
        std::unordered_map<T, std::pair<long long int, int>> indirectResults;
        std::size_t groupingDataSize{groupingData.size()};
        for (std::size_t i{0}; i < groupingDataSize; ++i)
        {
            auto& pair = indirectResults[groupingData[i]];
            pair.first += aggregateData[i];
            pair.second++;
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

    const static std::map<std::string, OperationType::Type>
        stringToOperationTypeMapping_;
};
