cmake_minimum_required(VERSION 3.15)
project(zenith LANGUAGES CXX)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SRCS 
    src/*.cpp 
    extern/*.cpp
)

# Add library
add_subdirectory(lib)

add_executable(zenith ${SRCS})

# Include directories
include_directories(extern)

# Link against lib
target_link_libraries(zenith PRIVATE zenithlib)

# Tests
option(ZENITH_TESTS ON)
if(ZENITH_TESTS)
    enable_testing()

    macro(my_add_test test_name)
        add_executable(${test_name} tests/${test_name}.cpp)
        add_test(NAME ${test_name} COMMAND ${test_name})
    endmacro()

    my_add_test(lexer)
endif()

