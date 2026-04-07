cmake_minimum_required(VERSION 3.23)


add_executable(retail_project   main.c 
                                core/inventory.c
                                core/data_storage.c)
target_include_directories(retail_project PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(retail_project PRIVATE libfio PRIVATE my_hashmap)



