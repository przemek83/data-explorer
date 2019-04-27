#include <sstream>
#include <fstream>
#include <string>
#include <memory>
#include <chrono>
#include <cassert>
#include <iomanip>
#include <unordered_map>
#include <string>

#include "FileDataLoader.h"
#include "Dataset.h"
#include "UserInterface.h"
#include "Query.h"

[[ noreturn ]] static void exitWithHelp()
{
    std::cerr << "Usage: <binary> file" << std::endl << " file - name of data file." << std::endl;
    exit(EXIT_FAILURE);
}

static std::string parseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        exitWithHelp();
    }

    return argv[1];
}

static std::string getTimeDiffAsString(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end)
{
    constexpr unsigned int MICROSECONDS_IN_SECOND = 1000000;
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::string timeDiffAsString = std::to_string(diff * 1.0 / MICROSECONDS_IN_SECOND);
    timeDiffAsString += "s";
    return timeDiffAsString;
}

int main(int argc, char* argv[])
{
    std::string fileName = parseArgs(argc, argv);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::unique_ptr<std::istream> inFile = std::make_unique<std::ifstream>(fileName);
    if (!inFile->good())
    {
        std::cerr << "Cannot open " << fileName << " file, exiting." << std::endl;
        return -1;
    }

    std::unique_ptr<FileDataLoader> loader(new FileDataLoader(std::move(inFile)));
    Dataset dataset(std::move(loader));

    if (!dataset.init())
    {
        std::cerr << "Cannot load data, exiting." << std::endl;
        return -1;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Data loaded in " << std::fixed << getTimeDiffAsString(begin, end) << std::endl;

    UserInterface::printCommandHelp();

    while (true)
    {
        UserInterface userInterface;
        Query userQuery;
        if (!userInterface.getValidatedUserQueryForDataset(dataset, userQuery))
        {
            continue;
        }

        if (userQuery.operation == Operation::OperationType::QUIT)
        {
            break;
        }

        begin = std::chrono::steady_clock::now();
        std::unordered_map<std::string, int> results = dataset.executeQuery(userQuery);
        end = std::chrono::steady_clock::now();

        for (const auto& [key, value] : results)
        {
            std:: cout << key << " " << value << std::endl;
        }

        std::cout << "Operation time = " << std::fixed << getTimeDiffAsString(begin, end) << std::endl;
    }

    return 0;
}
