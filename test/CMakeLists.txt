SET(PROJECT_TEST ${PROJECT_NAME}-test )

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    QueryTest.cpp
    IntegerColumnTest.cpp
    StringColumn.cpp
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE GTest::gtest_main ${PROJECT_NAME}-lib)

include(CTest)
include(GoogleTest)
gtest_discover_tests(${PROJECT_TEST})
