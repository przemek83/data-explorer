SET(PROJECT_TEST ${PROJECT_NAME}-tests)

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    QueryTest.cpp
    IntegerColumnTest.cpp
    StringColumnTest.cpp
    ColumnTest.cpp
    FileDataLoaderTest.cpp
    DatasetTest.cpp
    OperationTest.cpp
    UserInterfaceTest.cpp
    FakeLoader.cpp
    FakeLoader.h
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE GTest::gtest_main ${PROJECT_NAME}-lib cpputils)

include(CTest)
include(GoogleTest)
gtest_discover_tests(${PROJECT_TEST})
