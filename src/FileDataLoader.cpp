#include "FileDataLoader.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "Column.h"
#include "IntegerColumn.h"
#include "StringColumn.h"

FileDataLoader::FileDataLoader(std::unique_ptr<std::istream> stream)
    : stream_(std::move(stream))
{
}

bool FileDataLoader::loadData(std::vector<std::string>& headers,
                              std::vector<Column::ColumnType>& columnTypes,
                              std::vector<std::unique_ptr<Column>>& dataColumns)
{
    std::string line;

    std::getline(*stream_, line);
    headers = getHeaders(line);

    std::getline(*stream_, line);
    columnTypes = getColumnTypes(line);

    if (!initColumns(columnTypes, dataColumns))
        return false;

    if (!loadData(dataColumns, *stream_))
        return false;

    return true;
}

bool FileDataLoader::loadData(std::vector<std::unique_ptr<Column>>& dataColumns,
                              std::istream& infile) const
{
    int lineIndex = 0;
    std::string inputLine;
    size_t columnsCount = dataColumns.size();
    while (std::getline(infile, inputLine))
    {
        size_t currentPosition = 0;
        unsigned int index = 0;
        std::string token;
        while ((currentPosition = inputLine.find(DELIMITER)) !=
               std::string::npos)
        {
            token = inputLine.substr(0, currentPosition);
            if (index >= columnsCount ||
                !dataColumns[index]->addDataItem(token))
            {
                std::cerr << "Data corrupted, line " << lineIndex << ", column "
                          << index << ", value " << token << std::endl;
                return false;
            }

            inputLine.erase(0, currentPosition + DELIMITER_LENGTH);
            index++;
        }
        if (index >= columnsCount ||
            !dataColumns[index]->addDataItem(inputLine))
        {
            std::cerr << "Data corrupted, line " << lineIndex << ", column "
                      << index << ", value " << token << std::endl;
            return false;
        }
        lineIndex++;
    }

    return true;
}

std::vector<std::string> FileDataLoader::getHeaders(
    const std::string& inputLine) const
{
    std::vector<std::string> headers;

    std::stringstream input(inputLine);
    std::string header;
    while (std::getline(input, header, DELIMITER))
        headers.push_back(header);

    return headers;
}

std::vector<Column::ColumnType> FileDataLoader::getColumnTypes(
    const std::string& inputLine) const
{
    std::vector<Column::ColumnType> types;

    std::stringstream input(inputLine);
    std::string name;
    while (std::getline(input, name, DELIMITER))
    {
        if (const auto [success, type]{Column::getColumnType(name)}; success)
            types.push_back(type);
    }

    return types;
}

bool FileDataLoader::initColumns(
    const std::vector<Column::ColumnType>& columnTypes,
    std::vector<std::unique_ptr<Column>>& dataColumns) const
{
    for (Column::ColumnType columnType : columnTypes)
    {
        switch (columnType)
        {
            case Column::ColumnType::INTEGER:
            {
                dataColumns.emplace_back(
                    std::make_unique<IntegerColumn>(std::vector<int>()));
                break;
            }

            case Column::ColumnType::STRING:
            {
                dataColumns.emplace_back(std::make_unique<StringColumn>());
                break;
            }
        }
    }

    return true;
}
