cmake_minimum_required(VERSION 2.8)

FIND_PACKAGE (GTest)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src/include
)

add_executable(ATlibTest
    src/ATlibStringUtlTest.cpp
    src/ATlibSysUtlTest.cpp
    src/ATlibDateUtlTest.cpp
    src/ATlibVector2Test.cpp)

target_link_libraries(ATlibTest
    pthread
    ${GTEST_BOTH_LIBRARIES}
    ATlib
)

enable_testing()
add_test(A ATlibTest)
