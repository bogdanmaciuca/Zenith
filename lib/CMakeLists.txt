cmake_minimum_required(VERSION 3.15)    
project(zenithlib LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SRCS 
    src/*.cpp 
)

add_library(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Tests
option(ZENITH_LIB_TESTS "Build the zenith front-end tests" ON)
if(ZENITH_LIB_TESTS)
    add_subdirectory(tests)
endif()

