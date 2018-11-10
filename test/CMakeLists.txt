file(GLOB SOURCES "*.cpp")
add_executable(explorer-test ${SOURCES})

target_link_libraries(explorer-test gtest gtest_main explorer-lib)

add_test(NAME explorer-test COMMAND explorer-test)
