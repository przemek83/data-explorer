include_directories("${PROJECT_SOURCE_DIR}")

file(GLOB SOURCES "../*.cpp" "QueryTest.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*main.cpp$")

add_executable(explorer-test ${SOURCES})

target_link_libraries(explorer-test gtest gtest_main)
add_test(NAME explorer-test COMMAND explorer-test)
