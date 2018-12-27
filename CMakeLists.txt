cmake_minimum_required(VERSION 3.12)
project(GraphAlgos)

set(CMAKE_CXX_STANDARD 17)

file (GLOB SOURCE_FILES "lib/*.cpp")

set (GTEST_LIB_PATH "/home/anil/lib/googletest-release-1.8.0/googletest/libgtest.a")
set (GTEST_INCLUDE_PATH "/home/anil/lib/googletest-release-1.8.0/googletest/include/")
file(GLOB TestSource "test/*.cpp")

include_directories( ${GTEST_INCLUDE_PATH} )

add_executable(GraphAlgos main.cpp ${SOURCE_FILES} ${TestSource})
target_link_libraries(GraphAlgos ${GTEST_LIB_PATH} pthread)