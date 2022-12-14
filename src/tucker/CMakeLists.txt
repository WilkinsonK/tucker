# Build and linkages for project.
add_executable(${TUCKER_META_NAME} main.cpp)
target_link_libraries(${TUCKER_META_NAME} ${tuckerLibList})
