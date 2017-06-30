cmake_minimum_required(VERSION 3.7)
project(libSpikes)

set(CMAKE_CXX_STANDARD 11)

set(main.cpp)

# Setting up external libs
set(EXTERNAL_LIBS "${PROJECT_SOURCE_DIR}/libs")
INCLUDE_DIRECTORIES ( "${EXTERNAL_LIBS}" )

add_executable(libSpikes ${SOURCE_FILES} main.cpp)