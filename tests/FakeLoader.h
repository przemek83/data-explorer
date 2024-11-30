#pragma once

#include <src/DataLoader.h>

class FakeLoader : public DataLoader
{
public:
    bool loadData(std::vector<std::string>& headers,
                  std::vector<Column::ColumnType>& columnTypes,
                  std::vector<std::unique_ptr<Column>>& dataColumns) override;

    void setLoadDataResult(bool result);

private:
    bool loadDataResult_{true};
};