cmake_minimum_required(VERSION 3.10)
project(MyProgram LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

add_executable(breakoutPOP breakoutPOP.cpp)


target_include_directories(breakoutPOP PRIVATE ${RAYLIB_INCLUDE_DIRS})
target_compile_options(breakoutPOP PRIVATE ${RAYLIB_CFLAGS_OTHER})
target_link_directories(breakoutPOP PRIVATE ${RAYLIB_LIBRARY_DIRS})
target_link_libraries(breakoutPOP PRIVATE ${RAYLIB_LIBRARIES})
