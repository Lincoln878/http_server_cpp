cmake_minimum_required(VERSION 3.10)

project(http)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    http
    main.cpp
    http_server.cpp
)
target_include_directories(http PRIVATE .)