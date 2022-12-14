add_library(pluginLib "")

target_sources(pluginLib
    PRIVATE
        plugin.cpp
    PUBLIC
        plugin.hpp)

target_compile_definitions(pluginLib PUBLIC)
target_include_directories(pluginLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
