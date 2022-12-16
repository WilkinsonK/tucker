add_library(Tucker_cli_Lib "")
target_sources(Tucker_cli_Lib
    PRIVATE
        cli.cpp
    PUBLIC
        cli.hpp)

# Identify and link libraries
target_compile_definitions(Tucker_cli_Lib PUBLIC)

# This list is used to include all external
# libraries required to build this sub-module.
list(APPEND Tucker_cli_LibList)

# Include argparse if enabled at top-level.
if(TUCKER_USE_argparse_MODULE)
    list(APPEND Tucker_cli_LibList argparse)
endif()

target_link_libraries(Tucker_cli_Lib PRIVATE ${Tucker_cli_LibList})

target_include_directories(Tucker_cli_Lib
    PRIVATE
        ${argparse_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
