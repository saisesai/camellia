cmake_minimum_required(VERSION 3.15)

project(camellia)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third_party/fmt-11.1.0)
add_subdirectory(third_party/googletest-1.15.2)
add_subdirectory(third_party/libuv-1.49.2)

add_library(
        camellia_lib STATIC

        builtin/defer.cc

        common/mutex.cc
        common/thread.cc

        token/file.cc
        token/pos.cc
        token/position.cc
        token/token.cc
)
target_include_directories(camellia_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(camellia_lib PUBLIC fmt::fmt uv_a)

add_executable(
        camellia_test
        token/token_test.cc
)
target_link_libraries(camellia_test PRIVATE camellia_lib gtest gtest_main)

add_executable(camellia main.cc)
target_link_libraries(camellia PRIVATE camellia_lib)
