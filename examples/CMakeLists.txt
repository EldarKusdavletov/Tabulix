# Examples CMakeLists.txt

# Basic example
add_executable(basic_example basic_example.cpp)
target_link_libraries(basic_example PRIVATE tabulix)

# Advanced example
add_executable(advanced_example advanced_example.cpp)
target_link_libraries(advanced_example PRIVATE tabulix)
