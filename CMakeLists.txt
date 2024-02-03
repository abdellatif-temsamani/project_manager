project(project_manager)
cmake_minimum_required(VERSION 3.0)

set(SOURCE_FILES src/main.c src/utils.c src/inotify.c src/notify.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBNOTIFY REQUIRED libnotify)

include_directories(${LIBNOTIFY_INCLUDE_DIRS})
link_directories(${LIBNOTIFY_LIBRARY_DIRS})

target_link_libraries(project_manager ${LIBNOTIFY_LIBRARIES})
target_include_directories(project_manager PRIVATE src/include)
