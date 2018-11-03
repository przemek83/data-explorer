#ifndef FILEDATALOADER_H
#define FILEDATALOADER_H

#include <vector>

#include "DataLoader.h"

class IntegerColumn;
class StringColumn;

class FileDataLoader : public DataLoader
{
public:
    explicit FileDataLoader(std::string filePath);

    ~FileDataLoader() override = default;

    FileDataLoader& operator=(const FileDataLoader& other) = delete;
    FileDataLoader(const FileDataLoader& other) = delete;

    FileDataLoader& operator=(FileDataLoader&& other) = default;
    FileDataLoader(FileDataLoader&& other) = default;

    bool loadData(std::vector<std::string>& headers,
                  std::vector<Column::ColumnType>& columnTypes,
                  std::vector<std::unique_ptr<Column>>& dataColumns) const override;

private:
    std::vector<std::string> getHeaders(std::string& inputLine) const;

    std::vector<Column::ColumnType> getColumnTypes(std::string& inputLine) const;

    bool initColumns(std::vector<Column::ColumnType>& columnTypes, std::vector<std::unique_ptr<Column>>& dataColumns) const;

    bool loadData(std::vector<std::unique_ptr<Column>>& dataColumns, std::ifstream& infile) const;

    static const std::string delimiter_;

    const std::string filePath_;
};

#endif // FILEDATALOADER_H
