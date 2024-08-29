#pragma once

#include <vector>

#include "DataLoader.h"

class IntegerColumn;
class StringColumn;

class FileDataLoader : public DataLoader
{
public:
    explicit FileDataLoader(std::unique_ptr<std::istream> stream);

    bool loadData(std::vector<std::string>& headers,
                  std::vector<Column::ColumnType>& columnTypes,
                  std::vector<std::unique_ptr<Column>>& dataColumns) override;

private:
    std::vector<std::string> getHeaders(std::string& inputLine) const;

    std::vector<Column::ColumnType> getColumnTypes(
        const std::string& inputLine) const;

    bool initColumns(const std::vector<Column::ColumnType>& columnTypes,
                     std::vector<std::unique_ptr<Column>>& dataColumns) const;

    bool loadData(std::vector<std::unique_ptr<Column>>& dataColumns,
                  std::istream& infile) const;

    static constexpr char DELIMITER{';'};

    static constexpr unsigned int DELIMITER_LENGTH{1};

    std::unique_ptr<std::istream> stream_;
};
