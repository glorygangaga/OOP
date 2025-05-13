cmake_minimum_required(VERSION 3.10)

project(CComplexTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(CComplexTest
    CComplex.cpp
    test.cpp
)

find_package(GTest REQUIRED)

target_link_libraries(CComplexTest GTest::GTest GTest::Main)
target_include_directories(CComplexTest PRIVATE ${CMAKE_SOURCE_DIR})