# Initial setup of this sub-package library.
add_library(Tucker_api_Lib "")
target_sources(Tucker_api_Lib
    PRIVATE
        api.cpp
    PUBLIC
        api.hpp)

# Identify and link libraries
target_compile_definitions(Tucker_api_Lib PUBLIC)

# This list is used to include all external
# libraries required to build this sub-module.
list(APPEND Tucker_api_LibList)

# Include argparse if enabled at top-level.
if(TUCKER_USE_argparse_MODULE)
    list(APPEND Tucker_api_LibList argparse)
endif()

# Include cli sub-module if enabled at top-level.
if(TUCKER_USE_Tucker_cli_Lib_MODULE)
    list(APPEND Tucker_api_LibList Tucker_cli_Lib)
endif()
target_link_libraries(Tucker_api_Lib PRIVATE ${Tucker_api_LibList})

target_include_directories(Tucker_api_Lib
    PRIVATE
        ${argparse_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
