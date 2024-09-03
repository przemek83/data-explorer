#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include <cpputils/Logger.h>
#include <cpputils/Timer.h>

#include "Dataset.h"
#include "FileDataLoader.h"
#include "Query.h"
#include "UserInterface.h"

namespace
{
void showHelp()
{
    Log().error("Usage: <binary> file");
    Log().error(" file - name of data file.");
}

std::pair<bool, Dataset> createDataset(const std::string& fileName)
{
    Timer timer{Timer::Duration::MICROSECONDS};
    Log().info("Loading data");

    std::unique_ptr<std::istream> inFile =
        std::make_unique<std::ifstream>(fileName);
    if (!inFile->good())
    {
        Log().error("Cannot open " + fileName + " file, exiting.");
        return {false, Dataset{nullptr}};
    }

    auto loader{std::make_unique<FileDataLoader>(std::move(inFile))};
    Dataset dataset(std::move(loader));

    if (!dataset.init())
    {
        Log().error("Cannot load data, exiting.");
        return {false, Dataset{nullptr}};
    }

    return {true, std::move(dataset)};
}

void printCommandHelp()
{
    std::stringstream stringStream(std::ios_base::out);
    stringStream << "Usage:\n";
    stringStream << "<operation> <aggregation> <grouping>\n";
    stringStream << " operation = {"
                 << operation::getAvailableOperationsAsString("|") << "}\n";
    stringStream << " aggregation = column which will be used for aggreagation "
                    "(numerical only)\n";
    stringStream << " grouping = column which will be used for grouping";
    Log().info(stringStream.str());
}
};  // namespace

int main(int argc, char* argv[])
{
    if (const int expectedArgsc{2}; argc != expectedArgsc)
    {
        showHelp();
        return EXIT_FAILURE;
    }

    const std::string fileName{argv[1]};
    const auto [success, dataset]{createDataset(fileName)};
    if (!success)
        return EXIT_FAILURE;

    printCommandHelp();

    while (true)
    {
        Log().info({});
        std::string inputLine;
        getline(std::cin, inputLine);
        UserInterface ui{inputLine};
        Query userQuery;
        if (!ui.validateQuery(dataset, userQuery))
            continue;

        if (userQuery.operation_ == operation::Type::QUIT)
            return EXIT_SUCCESS;

        Timer timer{Timer::Duration::MICROSECONDS};
        std::unordered_map<std::string, int> results{
            dataset.executeQuery(userQuery)};

        for (const auto& [key, value] : results)
            Log().info(key + " " + std::to_string(value));
    }

    return EXIT_SUCCESS;
}
