cmake_minimum_required(VERSION 3.23)


add_executable(retail_project   main.c 
                                core/inventory_hashmap.c
                                core/data_storage.c
                                cli/cli.c
                                cli/inventory_handling.c
                                cli/input_validator.c)
target_include_directories(retail_project PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(retail_project PRIVATE libfio PRIVATE my_hashmap)

add_executable(retail_project_vector   main.c 
                                core/inventory_vector.c
                                core/data_storage.c
                                cli/cli.c
                                cli/inventory_handling.c
                                cli/input_validator.c)
target_include_directories(retail_project_vector PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(retail_project_vector PRIVATE libfio PRIVATE my_vector)

