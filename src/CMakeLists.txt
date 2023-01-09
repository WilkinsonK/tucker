# Set metadata as macros for tucker.
add_compile_definitions(TUCKER_META_NAME="${TUCKER_META_NAME}")
add_compile_definitions(TUCKER_META_VERSION="${TUCKER_META_VERSION}")
add_compile_definitions(TUCKER_EXEC_ROOT="${TUCKER_EXEC_ROOT}")

# Include our header files for compile/link time.
set(TUCKER_LOCAL_HEADERS ioutil.hpp rest.hpp sessions.hpp cmdline.hpp)

# Build and linkages for project.
add_executable(${TUCKER_META_NAME} main.cpp ${TUCKER_LOCAL_HEADERS})
target_link_libraries(${TUCKER_META_NAME}
    PRIVATE 
        restclient-cpp
        argparse::argparse)
