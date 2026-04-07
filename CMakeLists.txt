cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(C_EXTENSIONS OFF)

project(C_projects LANGUAGES C)
add_subdirectory(src)
add_subdirectory(lib)
