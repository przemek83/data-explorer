[![Build & test](https://github.com/przemek83/data-explorer/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/data-explorer/actions/workflows/buld-and-test.yml)
[![CodeQL](https://github.com/przemek83/data-explorer/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/przemek83/data-explorer/actions/workflows/github-code-scanning/codeql)
[![codecov](https://codecov.io/gh/przemek83/data-explorer/graph/badge.svg?token=SJF84CBY8Y)](https://codecov.io/gh/przemek83/data-explorer)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=przemek83_data-explorer&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=przemek83_data-explorer)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=przemek83_data-explorer&metric=bugs)](https://sonarcloud.io/summary/new_code?id=przemek83_data-explorer)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=przemek83_data-explorer&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=przemek83_data-explorer)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=przemek83_data-explorer&metric=coverage)](https://sonarcloud.io/summary/new_code?id=przemek83_data-explorer)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=przemek83_data-explorer&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=przemek83_data-explorer)

# About
Data Explorer is a tool for performing various operations on datasets. It supports operations like aggregation (average, minumum, maximum) and grouping, providing a simple interface for querying data.


# Building:  
Clone and use CMake with GCC/Clang/MSVC to compile the project and tests from an IDE or command line. CMake **should**:
- configure everything automatically,
- download and build dependency,
- compile and create binaries.

## Used tools and libs
| Tool |  Windows | Ubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 24.04 |
| GCC | 13.1.0 | 13.2.0 |
| CMake | 3.30.2 | 3.28.3 |
| Git | 2.46.0 | 2.43.0 |
| cpputils | ? | ? |

# Usage:  
## Launching:  
Launch binary and pass single param being file name containing data: 
```shell
$ data-explorer sample.txt
```
## Interface
Application expects series of commands as text lines. Each line should have following structure:
```
<operation> <aggregation column> <grouping column>  
```
where:
- `operation` is an aggregation functions of one of types:
    - `avg`: calculates the average of a set of values.
    - `min`: finds the minimum value in a set of values.
    - `max`: finds the maximum value in a set of values.
- `aggregation column` is numerical data column using which aggregation will be done.
- `grouping column` is column used for grouping results.


Usage Example:  
```shell
$ avg score movie_name
```

Example output:  
```
Execute: AVG score GROUPED BY movie_name
Execution time: 12us
Results:
ender's_game 8
pulp_fiction 6
inception 8
```

# License
This project is licensed under the MIT License. See the LICENSE file for details.

The project uses the following open-source software:
| Name | License | Home | Description |
| --- | --- | --- | --- |
| cpputils | MIT | https://github.com/przemek83/cpputils| collection of C++ utility classes |

# Testing
For testing purposes `gtest` framework is used. Build the project first. Make sure that the `data-explorer-test` target is built. Modern IDEs supporting CMake also support running tests with monitoring of failures. But in case you would like to run it manually, go to the `build/tests` directory, where the⁣ binary `data-explorer-test` should be available. Launching it should produce the following output on Linux:
    
    $ ./data-explorer-test 
    Running main() from <path>/data-explorer/build/_deps/googletest-src/googletest/src/gtest_main.cc
    [==========] Running 44 tests from 8 test suites.
    [----------] Global test environment set-up.
    [----------] 1 test from DataExplorer
    [ RUN      ] DataExplorer.executeQuery
    [       OK ] DataExplorer.executeQuery (0 ms)

    (...)

    [ RUN      ] UserInterfaceTest.GetQueryOperationWrongAggregatingColumn
    [       OK ] UserInterfaceTest.GetQueryOperationWrongAggregatingColumn (0 ms)
    [----------] 7 tests from UserInterfaceTest (0 ms total)

    [----------] Global test environment tear-down
    [==========] 44 tests from 8 test suites ran. (1 ms total)
    [  PASSED  ] 44 tests.


As an alternative, CTest can be used to run tests from `build` directory:

    $ ctest
    Test project <path>/data-explorer/build
        Start  1: DataExplorer.executeQuery
    1/44 Test  #1: DataExplorer.executeQuery ...................................   Passed    0.00 sec
 
    (...)

        Start 44: UserInterfaceTest.GetQueryOperationWrongAggregatingColumn
    44/44 Test #44: UserInterfaceTest.GetQueryOperationWrongAggregatingColumn ...   Passed    0.00 sec

    100% tests passed, 0 tests failed out of 44

    Total Test time (real) =   0.10 sec


# Additional info
As speed is most important expectations from task there was some optimization performed. Ones with biggest impact:  
* Used std::unordered_map instead of std::map.  
* Used std::vectors to store data and passed by const reference.  
* Storing strings as mapped values (std::string <-> unsigned int) and usage of indexes for operations (performance and significant memory optimisation).  
* Minimized copying.

# Potential further improvements
For bigger datasets and more sophisticated operations following enhancements might be viable:
* Usage for multithreading in calculations using std::async + std::future.  
* Usage of MPI (make sense with more sophisticated calculations).  
* GPU calculations (in case of more complex calculations).
