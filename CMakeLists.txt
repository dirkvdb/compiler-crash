cmake_minimum_required(VERSION 3.1)

project(Repro LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(repro
    geodb.h
    geoscheme.h
    geodb.cpp
)

target_include_directories(repro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/date/include
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlpp11/include
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlpp11-connector-sqlite3/include
)