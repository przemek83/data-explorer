[![Build & test](https://github.com/przemek83/data-explorer/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/data-explorer/actions/workflows/buld-and-test.yml)
[![CodeQL](https://github.com/przemek83/data-explorer/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/przemek83/data-explorer/actions/workflows/github-code-scanning/codeql)
[![codecov](https://codecov.io/gh/przemek83/data-explorer/graph/badge.svg?token=SJF84CBY8Y)](https://codecov.io/gh/przemek83/data-explorer)

## Building:  
Use compiler directly:
```shell
$ g++ -Wall -std=c++17 -Isrc -O3 -c *.cpp src/*.cpp  
$ g++ -Wall -std=c++17 -O3 -o data-explorer *.o  
```
OR  
use CMake + GCC/Clang to compile project and tests (from some IDE or cmd).  

## Execution:  
```shell
$ data-explorer sample.txt
```

## Usage:  
\<operation\> \<aggregation\> \<grouping\>  

Usage Example:  
```shell
$ avg score movie_name
```

Example output:  
```
avg score GROUPED BY movie_name  
ender's_game 8  
pulp_fiction 6  
inception 8  
Operation time = 0.000009s  
```

## Files:  
main.cpp - main file :)  
Column.[h|cpp] - Abstract and base class for column inheritance hierarchy.  
IntegerColumn.[h|cpp] - Class for storing data and performing operations on integer type columns.   
StringColumn.[h|cpp] - Class for storing data and performing operations on string type columns.   
DataLoader.h - Abstract and base class for data loaders.  
FileDataLoader.[h|cpp] - File data loader. Loads from file headers, types and finally data.  
Dataset.[h|cpp] - Representation of data. Contains info about headers, column types and stores Column class objects.  
Operation.[h|cpp] - Stores enum OperationType. Also "math" is done here using some templates.  
Query.h - Trivial structure for storing which query user requested.  
UserInterface.[h|cpp] - Functionalities related to interaction with user.  

## Additional info
As speed is most important expectations from task there was some optimization performed. Ones with biggest impact:  
1) Used std::unordered_map instead of std::map.  
2) Used std::vectors to store data and passed by const reference.  
3) Storing strings as mapped values (std::string <-> unsigned int) and usage of indexes for operations (performance and significant memory optimisation).  
4) Minimized copying.

Potential further optimizations:  
1) Usage of dynamic C-style arrays for storage. To introduce those input file need to be passed 2 times (first to check number of rows).  
2) Usage of C-style array + index instead of maps (if applicable and worth doing).  

Potential options for scalability:  
1) Usage for multithreading by introducing threads.  
2) Usage of MPI (make sense with more sophisticated calculations).  
3) GPU calculations (in case of more complex calculations).

I'm not fully happy about:  
1) Template usage.  
2) Allowing accessing private field data of Column subclasses from outside (performance reasons).
