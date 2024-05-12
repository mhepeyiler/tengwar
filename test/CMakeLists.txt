
set(TEST_BIN_NAME ${PROJECT_NAME}_test)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/test/bin")

find_package(GTest REQUIRED)

add_custom_target(create_link ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_LIST_DIR}/files ${PROJECT_BINARY_DIR}/test/bin/files)

add_executable(${TEST_BIN_NAME} src/main.cpp
                                src/reader_test.cpp
                                src/lexer_test.cpp)

target_include_directories(${TEST_BIN_NAME} PUBLIC include)

target_link_libraries(${TEST_BIN_NAME} 
                                    PUBLIC gtest::gtest
                                    PUBLIC ${PROJECT_SHARED_LIB_OUTPUT})