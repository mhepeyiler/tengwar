cmake_minimum_required(VERSION 3.22)

project(tengwar VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

set(PROJECT_SHARED_LIB_OUTPUT ${PROJECT_NAME}_SHARED)

add_library(${PROJECT_SHARED_LIB_OUTPUT}
src/freader.cpp
src/lexer.cpp)

target_include_directories(${PROJECT_SHARED_LIB_OUTPUT} PUBLIC include)

add_executable(${PROJECT_NAME} src/main.cpp)


    enable_testing()
    add_subdirectory(test)
