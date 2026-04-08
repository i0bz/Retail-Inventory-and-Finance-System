cmake_minimum_required(VERSION 3.23)

project(my_vector LANGUAGES C)

add_library(my_vector STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.c)

set_target_properties(my_hashmap PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)



target_include_directories(my_vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)