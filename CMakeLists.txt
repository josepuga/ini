cmake_minimum_required(VERSION 3.0.0)
project(ini VERSION 0.1.0) #project must be BEFORE to detect compiler with CMAKE_CXX_COMPILER_ID

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17 -ggdb")
if(WIN32)
    message("Windows detected. Linking statically...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static -pthread")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Building Debug...")
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building Release...")
endif()

include_directories(src)

add_executable(demo_ini 
    test/demo_ini.cpp 
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
