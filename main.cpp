#include <sstream>
#include <iostream>
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

[[ noreturn ]] void exitWithHelp()
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

static void testResults(const std::unordered_map<std::string, int>& current, const std::unordered_map<std::string, int>& expected)
{
    if (current != expected)
    {
        std::cout << "test failed, expected: ";
        for (auto& pair : expected)
        {
            std:: cout << "(" + pair.first << "," << pair.second << ") ";
        }

        std::cout << ", current: ";

        for (auto& pair : current)
        {
            std:: cout << "(" + pair.first << "," << pair.second << ") ";
        }

        std::cout << std::endl;
    }
}

static void test()
{
    std::unique_ptr<FileDataLoader> loader(new FileDataLoader("sample.txt"));
    Dataset dataset(std::move(loader));

    if (!dataset.init())
    {
        std::cerr << "Cannot load data, exiting." << std::endl;
        return;
    }

    Query query {Operation::OperationType::MIN, 1, 0};
    std::unordered_map<std::string, int> expected {{"tim", 26}, {"tamas", 44}, {"dave", 0}};
    testResults(dataset.executeQuery(query), expected);

    query = {Operation::OperationType::MAX, 3, 2};
    expected = {{"inception", 8}, {"pulp_fiction", 8}, {"ender's_game", 8}};
    testResults(dataset.executeQuery({Operation::OperationType::MAX, 3, 2}), expected);

    query = {Operation::OperationType::AVG, 3, 0};
    expected = std::unordered_map<std::string, int> {{"tim", 8}, {"tamas", 6}, {"dave", 8}};
    testResults(dataset.executeQuery(query), expected);
}

int main(int argc, char* argv[])
{
    std::string fileName = parseArgs(argc, argv);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::unique_ptr<FileDataLoader> loader(new FileDataLoader(fileName));
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

        if (userQuery.operation == Operation::OperationType::TEST)
        {
            test();
            continue;
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
