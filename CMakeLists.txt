
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

# Modules and meta-information for Tucker.
include(FetchContent)

set(TUCKER_META_NAME tucker)
set(TUCKER_META_VERSION 0.0.0)
set(TUCKER_EXEC_ROOT $ENV{PWD})

# Setup initial project and project definitions.
project(${TUCKER_META_NAME} VERSION ${TUCKER_META_VERSION})

add_compile_definitions(TUCKER_META_NAME="${TUCKER_META_NAME}")
add_compile_definitions(TUCKER_META_VERSION="${TUCKER_META_VERSION}")
add_compile_definitions(TUCKER_EXEC_ROOT="${TUCKER_EXEC_ROOT}")

# This list is used to include all external
# libraries needed for this project.
list(APPEND tuckerLibList)

# Fetch argparse.
if(true)
    FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
        GIT_TAG v2.9)
    FetchContent_MakeAvailable(argparse)
    FetchContent_GetProperties(argparse)
endif()

# Include project local directories.
# mkmod[BEGIN]
if(true)
    add_subdirectory(src/api)
    find_library(Tucker_api_Lib src/api)
    list(APPEND tuckerLibList Tucker_api_Lib)
endif()
# mkmod[END]

# Include this project application.
add_subdirectory(src/tucker)
