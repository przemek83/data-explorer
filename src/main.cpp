#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Dataset.h"
#include "FileDataLoader.h"
#include "Logger.h"
#include "Query.h"
#include "UserInterface.h"

namespace
{
void showHelp()
{
    Logger().logErr("Usage: <binary> file");
    Logger().logErr(" file - name of data file.");
}

std::string getTimeDiffAsString(std::chrono::steady_clock::time_point begin,
                                std::chrono::steady_clock::time_point end)
{
    constexpr unsigned int MICROSECONDS_IN_SECOND = 1'000'000;
    auto diff =
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
            .count();
    std::string timeDiffAsString =
        std::to_string(static_cast<double>(diff) / MICROSECONDS_IN_SECOND);
    timeDiffAsString += "s";
    return timeDiffAsString;
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

    std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();

    std::unique_ptr<std::istream> inFile =
        std::make_unique<std::ifstream>(fileName);
    if (!inFile->good())
    {
        Logger().logErr("Cannot open " + fileName + " file, exiting.");
        return EXIT_FAILURE;
    }

    auto loader{std::make_unique<FileDataLoader>(std::move(inFile))};
    Dataset dataset(std::move(loader));

    if (!dataset.init())
    {
        Logger().logErr("Cannot load data, exiting.");
        return EXIT_FAILURE;
    }

    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    std::stringstream stream;
    stream << "Data loaded in " << std::fixed
           << getTimeDiffAsString(begin, end);
    Logger().logMsg(stream.str());

    UserInterface::printCommandHelp();

    while (true)
    {
        UserInterface userInterface;
        Query userQuery;
        if (!userInterface.getValidatedUserQueryForDataset(dataset, userQuery))
        {
            continue;
        }

        if (userQuery.operation_ == operation::Type::QUIT)
        {
            break;
        }

        begin = std::chrono::steady_clock::now();
        std::unordered_map<std::string, int> results =
            dataset.executeQuery(userQuery);
        end = std::chrono::steady_clock::now();

        for (const auto& [key, value] : results)
        {
            stream.str("");
            stream << key << " " << value;
            Logger().logMsg(stream.str());
        }

        stream.str("");
        stream << "Operation time = " << std::fixed
               << getTimeDiffAsString(begin, end);
        Logger().logMsg(stream.str());
    }

    return EXIT_SUCCESS;
}
