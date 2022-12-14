add_library(tuckerAPIlib "")

target_sources(tuckerAPIlib
    PRIVATE
        api.cpp
    PUBLIC
        api.hpp
)

target_compile_definitions(tuckerAPIlib PUBLIC)
target_include_directories(tuckerAPIlib PUBLIC ${CMAKE_CURRENT_LIST_DIR})
