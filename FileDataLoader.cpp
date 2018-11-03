#include "FileDataLoader.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

#include "IntegerColumn.h"
#include "StringColumn.h"
#include "Column.h"

const std::string FileDataLoader::delimiter_{" "};

FileDataLoader::FileDataLoader(std::string filePath) : filePath_(std::move(filePath))
{

}

bool FileDataLoader::loadData(std::vector<std::string>& headers,
                              std::vector<Column::ColumnType>& columnTypes,
                              std::vector<std::unique_ptr<Column>>& dataColumns) const
{
    std::ifstream infile(filePath_);
    if (!infile.good())
    {
        return false;
    }

    std::string line;

    std::getline(infile, line);
    headers = getHeaders(line);

    std::getline(infile, line);
    columnTypes = getColumnTypes(line);

    if (!initColumns(columnTypes, dataColumns))
    {
        return false;
    }

    if (!loadData(dataColumns, infile))
    {
        return false;
    }

    return true;
}

bool FileDataLoader::loadData(std::vector<std::unique_ptr<Column>>& dataColumns, std::ifstream& infile) const
{
    int lineIndex = 0;
    std::string inputLine;
    size_t columnsCount = dataColumns.size();
    while (std::getline(infile, inputLine))
    {
        size_t currentPosition = 0;
        unsigned int index = 0;
        std::string token;
        while ((currentPosition = inputLine.find(delimiter_)) != std::string::npos)
        {
            token = inputLine.substr(0, currentPosition);
            if (index >= columnsCount)
            {
                std::cerr << "Data corrupted, line " << lineIndex << ", column " <<
                    index << ", value " << token << std::endl;
                return false;
            }
            dataColumns[index]->addDataItem(token);
            inputLine.erase(0, currentPosition + delimiter_.length());
            index++;
        }
        if (index >= columnsCount)
        {
            std::cerr << "Data corrupted, line " << lineIndex << ", column " <<
                index << ", value " << token << std::endl;
            return false;
        }
        dataColumns[index]->addDataItem(inputLine);
        lineIndex++;
    }

    return true;
}

std::vector<std::string> FileDataLoader::getHeaders(std::string& inputLine) const
{
    std::vector<std::string> headers;

    size_t currentPosition = 0;
    while ((currentPosition = inputLine.find(delimiter_)) != std::string::npos)
    {
        headers.emplace_back(inputLine.substr(0, currentPosition));
        inputLine.erase(0, currentPosition + delimiter_.length());
    }
    headers.emplace_back(inputLine);

    return headers;
}

std::vector<Column::ColumnType> FileDataLoader::getColumnTypes(std::string& inputLine) const
{
    std::vector<Column::ColumnType> columnTypes;

    size_t currentPosition = 0;
    while ((currentPosition = inputLine.find(delimiter_)) != std::string::npos)
    {
        columnTypes.emplace_back(Column::getColumnTypeForName(inputLine.substr(0, currentPosition)));
        inputLine.erase(0, currentPosition + delimiter_.length());
    }
    columnTypes.emplace_back(Column::getColumnTypeForName(inputLine));

    return columnTypes;
}

bool FileDataLoader::initColumns(std::vector<Column::ColumnType>& columnTypes, std::vector<std::unique_ptr<Column>>& dataColumns) const
{
    for (Column::ColumnType columnType : columnTypes)
    {
        switch (columnType)
        {
            case Column::ColumnType::INTEGER:
            {
                dataColumns.emplace_back(std::make_unique<IntegerColumn>(std::vector<int>()));
                break;
            }

            case Column::ColumnType::STRING:
            {
                dataColumns.emplace_back(std::make_unique<StringColumn>());
                break;
            }

            default:
            {
                std::cout << "Unknown column type " << static_cast<int>(columnType) << std::endl;
                return false;
            }
        }
    }

    return true;
}
