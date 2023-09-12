cmake_minimum_required(VERSION 3.16)
project(LibUtils)

set(CMAKE_CXX_STANDARD 20)

add_library(LibUtils INTERFACE)

target_include_directories(LibUtils INTERFACE include)