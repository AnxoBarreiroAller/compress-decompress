cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
set(CMAKE_CXX_FLAGS "-std=c99")

PROJECT(compress_decompress)
set (SOURCE main.c compress.c decompress.c)
 
add_executable (${PROJECT_NAME} ${SOURCE})
