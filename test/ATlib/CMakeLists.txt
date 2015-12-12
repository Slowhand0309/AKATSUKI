FIND_PACKAGE (GTest REQUIRED)

set (HOME ../../)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${HOME}/src/include
)

add_executable(ATlibTest ${PROJECT_SOURCE_DIR}/src/ATlibTest.cpp)
target_link_libraries(ATlibTest
    pthread
    ${GTEST_BOTH_LIBRARIES}
)
