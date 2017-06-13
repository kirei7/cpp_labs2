cmake_minimum_required(VERSION 3.7)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES7 lab7/main.cpp lab7/Husband.cpp lab7/Product.cpp lab7/shops.cpp lab7/Wife.cpp)
add_executable(untitled1-7 ${SOURCE_FILES7})

set(SOURCE_FILES8 lab8/main.cpp)
add_executable(untitled1-8 ${SOURCE_FILES8} lab8/main.cpp)

