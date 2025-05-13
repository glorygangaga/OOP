cmake_minimum_required(VERSION 3.10)

project(UrlParser)

set(CMAKE_CXX_STANDARD 17)

add_executable(parser
    main.cpp
    app.cpp
    CHttpUrl.cpp
)

find_package(GTest REQUIRED)

add_executable(UrlParserTest
    test.cpp
    app.cpp
    CHttpUrl.cpp
)

target_link_libraries(UrlParserTest GTest::GTest GTest::Main pthread)
target_include_directories(UrlParserTest PRIVATE ${CMAKE_SOURCE_DIR})
