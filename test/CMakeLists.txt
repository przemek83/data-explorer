SET(PROJECT_TEST ${PROJECT_NAME}-test )

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    QueryTest.cpp
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE gtest gtest_main ${PROJECT_NAME}-lib)

include(CTest)
add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})
