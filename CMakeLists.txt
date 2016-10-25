cmake_minimum_required(VERSION 2.8)

project(AKATSUKI)

include_directories(
   src/include
)

add_definitions(-D_DEBUG)

add_subdirectory(src/projects/ATlib)
add_subdirectory(src/projects/ATgae)
add_subdirectory(test/ATlib)
