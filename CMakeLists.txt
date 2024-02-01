project(project_manager)
cmake_minimum_required(VERSION 3.0)

add_executable(project_manager src/main.c src/utils.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNOTIFY REQUIRED libnotify)

include_directories(${LIBNOTIFY_INCLUDE_DIRS})
link_directories(${LIBNOTIFY_LIBRARY_DIRS})

target_link_libraries(project_manager ${LIBNOTIFY_LIBRARIES})
target_include_directories(project_manager PRIVATE src/include)
