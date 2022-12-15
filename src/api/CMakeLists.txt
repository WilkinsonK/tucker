add_library(Tucker_api_Lib "")
target_sources(Tucker_api_Lib
    PRIVATE
        api.cpp
    PUBLIC
        api.hpp)

target_compile_definitions(Tucker_api_Lib PUBLIC)
target_link_libraries(Tucker_api_Lib PRIVATE argparse)
target_include_directories(Tucker_api_Lib
    PRIVATE
        ${argparse_SOURCE_DIR}/include
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
