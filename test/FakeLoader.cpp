#include "FakeLoader.h"

#include <src/IntegerColumn.h>
#include <src/StringColumn.h>

bool FakeLoader::loadData(std::vector<std::string>& headers,
                          std::vector<Column::ColumnType>& columnTypes,
                          std::vector<std::unique_ptr<Column>>& dataColumns)
{
    if (!loadDataResult_)
        return false;

    headers = {"h1", "h2", "h3"};
    columnTypes = {Column::ColumnType::INTEGER, Column::ColumnType::INTEGER,
                   Column::ColumnType::STRING};

    dataColumns.push_back(
        std::make_unique<IntegerColumn>(std::vector<int>{1, 2, 3, 11, 12, 13}));
    dataColumns.push_back(
        std::make_unique<IntegerColumn>(std::vector<int>{4, 5, 6, 14, 15, 16}));

    auto stringColumn{std::make_unique<StringColumn>()};
    stringColumn->addItem("Entry1");
    stringColumn->addItem("Entry2");
    stringColumn->addItem("Entry3");
    stringColumn->addItem("Entry1");
    stringColumn->addItem("Entry2");
    stringColumn->addItem("Entry3");
    dataColumns.push_back(std::move(stringColumn));

    return true;
}

void FakeLoader::setLoadDataResult(bool result) { loadDataResult_ = result; }
