cmake_minimum_required(VERSION 3.23)

project(my_hashmap LANGUAGES C)

add_library(my_hashmap STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/hashmap.c)

set_target_properties(my_hashmap PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libhashmap
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libhashmap
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libhashmap
)



target_include_directories(my_hashmap PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

