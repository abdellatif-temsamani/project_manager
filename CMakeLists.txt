project(project_manager)
cmake_minimum_required(VERSION 3.0)
add_executable(project_manager src/main.c src/utils.c)

target_include_directories(project_manager PRIVATE src/include)
