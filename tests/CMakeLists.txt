# Tests CMakeLists.txt

# Find Google Test
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Table tests
add_executable(table_tests table_tests.cpp)
target_link_libraries(table_tests PRIVATE tabulix GTest::gtest_main)
add_test(NAME table_tests COMMAND table_tests)

# Border tests
add_executable(border_tests border_tests.cpp)
target_link_libraries(border_tests PRIVATE tabulix GTest::gtest_main)
add_test(NAME border_tests COMMAND border_tests)

# Exporter tests
add_executable(exporter_tests exporter_tests.cpp)
target_link_libraries(exporter_tests PRIVATE tabulix GTest::gtest_main)
add_test(NAME exporter_tests COMMAND exporter_tests)
