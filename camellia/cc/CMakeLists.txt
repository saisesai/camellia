cmake_minimum_required(VERSION 3.15)

project(camellia)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        camellia
        main.cc
        token/token.cc
        token/utils.cc
)