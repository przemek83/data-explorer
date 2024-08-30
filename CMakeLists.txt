cmake_minimum_required(VERSION 3.14)

project(data-explorer
        LANGUAGES CXX
        VERSION 1.0.0
        DESCRIPTION "Small tool for aggregating and grouping data."
        HOMEPAGE_URL "https://github.com/przemek83/data-explorer")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CODE_COVERAGE "Collect coverage" OFF)

if(CODE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif()

set(${PROJECT_NAME}_SOURCES
    src/Column.cpp
    src/Column.h
    src/DataLoader.h
    src/Dataset.cpp
    src/Dataset.h
    src/FileDataLoader.cpp
    src/FileDataLoader.h
    src/IntegerColumn.cpp
    src/IntegerColumn.h
    src/Operation.cpp
    src/Operation.h
    src/Query.h
    src/StringColumn.cpp
    src/StringColumn.h
    src/UserInterface.cpp
    src/UserInterface.h
    src/Logger.h
    src/Timer.h
)

add_library (${PROJECT_NAME}-lib STATIC ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME}-lib)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

enable_testing()
Include(Tests.cmake)
add_subdirectory(test)
