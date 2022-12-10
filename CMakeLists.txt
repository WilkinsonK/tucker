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

# Fetch argparse.
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG v2.9)
FetchContent_MakeAvailable(argparse)

add_library(pluginLib "")
add_subdirectory(src/plugin)

target_sources(pluginLib
    PRIVATE
        src/plugin/metadata.cpp
        src/plugin/metadata.hpp
        src/plugin/object.hpp
        src/plugin/source.cpp
        src/plugin/source.hpp
    PUBLIC
        src/plugin/plugin.hpp)

target_compile_definitions(pluginLib PUBLIC)
target_include_directories(pluginLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# Build and linkages for project.
add_executable(${TUCKER_META_NAME} src/main.cpp)
target_link_libraries(${TUCKER_META_NAME} argparse pluginLib)
