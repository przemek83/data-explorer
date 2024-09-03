#include "FileDataLoader.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <cpputils/Logger.h>

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
    int index = 0;
    std::string line;
    while (std::getline(infile, line))
    {
        ++index;
        if (!processLine(dataColumns, line, index))
            return false;
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

            default:
                return false;
        }
    }

    return true;
}

bool FileDataLoader::processLine(
    std::vector<std::unique_ptr<Column>>& dataColumns, const std::string& line,
    int index) const
{
    const std::size_t columnsCount{dataColumns.size()};
    std::stringstream input(line);
    for (std::size_t i{0}; i < columnsCount; ++i)
    {
        std::string item;
        std::getline(input, item, DELIMITER);
        if (input.fail() || (!dataColumns[i]->addItem(item)))
        {
            Log().error("No data, line " + std::to_string(index) + ", column " +
                        std::to_string(i));

            return false;
        }
    }

    if (!input.eof())
    {
        Log().error("More data entries than expected, line " +
                    std::to_string(index));
        return false;
    }

    return true;
}
