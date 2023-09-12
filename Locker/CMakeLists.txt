cmake_minimum_required(VERSION 3.16)
project(Locker)

set(CMAKE_CXX_STANDARD 20)

add_library(Locker STATIC source/Locker.cpp)

target_include_directories(Locker PUBLIC include)