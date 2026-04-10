cmake_minimum_required(VERSION 3.23)

project(my_qsort LANGUAGES C)

add_library(my_qsort STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/quicksort.c)

set_target_properties(my_hashmap PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)



target_include_directories(my_qsort PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

