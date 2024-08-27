#pragma once

#include <memory>
#include <vector>

#include "Column.h"

class StringColumn : public Column
{
public:
    ColumnType getColumnType() const override;

    inline void addDataItem(const std::string& dataItem) override final
    {
        auto element = stringToIdMapping_.find(dataItem);
        if (element != stringToIdMapping_.end())
        {
            data_.push_back(element->second);
        }
        else
        {
            stringToIdMapping_[dataItem] = ++currentIndex_;
            data_.push_back(currentIndex_);
        }
    }

    const std::vector<unsigned int>& getData() const;

    std::unordered_map<std::string, int> performOperation(
        Operation::OperationType operationType,
        const std::vector<int>& data) const override;

private:
    std::vector<unsigned int> data_{};

    std::unordered_map<std::string, unsigned int> stringToIdMapping_{};

    unsigned int currentIndex_{0};
};
