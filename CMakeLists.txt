cmake_minimum_required(VERSION 3.7)
project(libSpikes)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

set(CMAKE_CXX_STANDARD 11)

# Setting all headders and srcs
file(
        GLOB
        src
        "${CMAKE_CURRENT_SOURCE_DIR}/libSpikes/src/Core/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/libSpikes/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/libSpikes/src/Core/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/libSpikes/src/*.h"
)


set(main.cpp)

# Setting up external libs
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/libs")
set(EXTERNAL_LIBS_WINDOWS "${PROJECT_SOURCE_DIR}/winLibs")

INCLUDE_DIRECTORIES ( "${EXTERNAL_LIBS}" )

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    INCLUDE_DIRECTORIES ( "${EXTERNAL_LIBS_WINDOWS}" )
    message(${CMAKE_CXX_COMPILER_ID})
endif()



add_executable(libSpikes ${SOURCE_FILES} main.cpp ${src} libSpikes/src/Core/alphanum.h)