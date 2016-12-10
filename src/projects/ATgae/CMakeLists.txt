cmake_minimum_required(VERSION 2.8)

project(AKATSUKI)

set(ATGAE_SRC
    engine/core/ATgaeCore.cpp
    engine/core/ATgaeCoreGL.cpp
    engine/core/ATgaeCoreDrawGL.cpp
    engine/impl/ATgaeImplGL.cpp
    engine/window/ATgaeWindowInfo.cpp
    engine/window/ATgaeWindowManager.cpp
    engine/ATgaeEngine.cpp
    engine/ATgaeEngineCreator.cpp
    debugger/ATgaeLog.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/include
)

add_library(ATgae STATIC
    ${ATGAE_SRC}
)
