cmake_minimum_required(VERSION 3.23)


file(GLOB c_files "*.c")

foreach(source_file ${c_files})
    get_filename_component(exec_name ${source_file} NAME_WE)
    add_executable(${exec_name})
    target_sources(${exec_name} PRIVATE ${source_file})
    target_include_directories(${exec_name} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    set_target_properties(${exec_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
endforeach()




