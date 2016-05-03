cmake_minimum_required(VERSION 2.8)

project(AKATSUKI)

set(ATGAE_SRC
    engine/window/ATgaeWindowInfo.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/include
)

add_library(ATgae STATIC
    ${ATGAE_SRC}
)
