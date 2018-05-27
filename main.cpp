#include <sstream>
#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <cassert>
#include <iomanip>

#include "FileDataLoader.h"
#include "Dataset.h"
#include "UserInterface.h"
#include "Query.h"

void exitWithHelp()
{
    std::cerr << "Usage: <binary> file" << std::endl << " file - name of data file." << std::endl;
    exit(EXIT_FAILURE);
}

std::string parseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        exitWithHelp();
    }

    std::string filePath = argv[1];

    return filePath;
}

int main(int argc, char* argv[])
{
    std::string filePath = parseArgs(argc, argv);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::unique_ptr<FileDataLoader> loader(new FileDataLoader(filePath));
    Dataset dataset(std::move(loader));

    if (!dataset.init())
    {
        std::cerr << "Cannot load data, exiting." << std::endl;
        return -1;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Data loaded in " << std::fixed <<
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0 << "s" << std::endl;

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

        auto begin = std::chrono::steady_clock::now();
        std::unordered_map<std::string, int> results = dataset.executeQuery(userQuery);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        for (auto& pair : results)
        {
            std:: cout << pair.first << " " << pair.second << std::endl;
        }

        std::cout << "Operation time = " << std::fixed <<
            std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0 << "s" << std::endl;
    }

    return 0;
}
