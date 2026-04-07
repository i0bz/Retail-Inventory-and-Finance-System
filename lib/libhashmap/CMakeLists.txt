cmake_minimum_required(VERSION 3.23)

project(my_hashmap LANGUAGES C)

add_library(my_hashmap STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/hashmap.c)

set_target_properties(my_hashmap PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)



target_include_directories(my_hashmap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

