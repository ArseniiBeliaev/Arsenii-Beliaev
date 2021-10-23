cmake_minimum_required(VERSION 3.0)
project(prac1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(MAXLENGTH_SRC ${CMAKE_SOURCE_DIR}/../PrintLengthMaxPrefix.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

add_executable(MAXLENGTH_TEST ${MAXLENGTH_SRC} MaxLength_test.cpp)

target_link_libraries(
        MAXLENGTH_TEST
        Threads::Threads
        ${GTEST_LIBRARIES}
        ${GMOCK_BOTH_LIBRARIES}
        )

include_directories(${CMAKE_SOURCE_DIR}/../include)
 
link_libraries(gtest gtest_main pthread)