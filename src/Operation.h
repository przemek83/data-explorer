#pragma once

#include <math.h>
#include <cstdint>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class Operation
{
public:
    enum class OperationType : uint8_t
    {
        AVG = 0,
        MIN,
        MAX,
        QUIT,
        UNKNOWN
    };

    Operation() = delete;
    ~Operation() = delete;

    static OperationType getOperationTypeForString(
        const std::string& operationTypeString);

    static std::string getAvailableOperationsAsString(
        const std::string& delimiter);

    template <class T>
    static std::unordered_map<T, int> executeOperation(
        OperationType operationType, const std::vector<T>& groupingData,
        const std::vector<int>& aggregateData)
    {
        std::unordered_map<T, int> results;

        switch (operationType)
        {
            case OperationType::AVG:
            {
                results = computeAverage<T>(groupingData, aggregateData);
                break;
            }

            case OperationType::MIN:
            {
                results =
                    computeExtremum<T>(groupingData, aggregateData,
                                       [](int a, int b) { return a > b; });
                break;
            }

            case OperationType::MAX:
            {
                results =
                    computeExtremum<T>(groupingData, aggregateData,
                                       [](int a, int b) { return a <= b; });
                break;
            }

            default:
            {
                throw std::logic_error("Unknown Operation Type " +
                                       static_cast<int>(operationType));
            }
        }
        return results;
    }

private:
    template <class T, class Func>
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

    template <class T>
    static std::unordered_map<T, int> computeAverage(
        const std::vector<T>& groupingData,
        const std::vector<int>& aggregateData)
    {
        std::unordered_map<T, std::pair<long long int, int>> indirectResults;
        unsigned int groupingDataSize = groupingData.size();
        for (unsigned int i = 0; i < groupingDataSize; ++i)
        {
            auto& pair = indirectResults[groupingData[i]];
            pair.first += aggregateData[i];
            pair.second++;
        }

        std::unordered_map<T, int> results;
        for (const auto& item : indirectResults)
        {
            results[item.first] = round(static_cast<float>(item.second.first) /
                                        item.second.second);
        }

        return results;
    }

    const static std::map<std::string, OperationType>
        stringToOperationTypeMapping_;
};
