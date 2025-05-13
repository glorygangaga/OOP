cmake_minimum_required(VERSION 3.10)

project(CMyStack)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(CMyStackTest
    test.cpp
    CMyStack.cpp
)

target_link_libraries(CMyStackTest GTest::GTest GTest::Main pthread)
target_include_directories(CMyStackTest PRIVATE ${CMAKE_SOURCE_DIR})
