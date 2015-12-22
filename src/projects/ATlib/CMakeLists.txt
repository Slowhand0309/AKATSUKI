cmake_minimum_required(VERSION 2.8)

project(AKATSUKI)

set(ATLIB_SRC
    io/ATlibFile.cpp
    io/ATlibLock.cpp
    io/ATlibStream.cpp
    utl/ATlibStringUtl.cpp
    utl/ATlibSysUtl.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/include
)

add_library(ATlib STATIC
    ${ATLIB_SRC}
)
