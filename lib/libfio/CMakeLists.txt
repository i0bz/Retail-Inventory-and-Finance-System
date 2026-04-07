cmake_minimum_required(VERSION 3.23)

project(file_io_library LANGUAGES C)

add_library(libfio STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/libfio.c)

set_target_properties(libfio PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)



target_include_directories(libfio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)