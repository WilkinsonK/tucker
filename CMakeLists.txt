
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)

# Modules and meta-information for Tucker.
set(TUCKER_META_NAME tucker)
set(TUCKER_META_VERSION 0.0.0)
set(TUCKER_EXEC_ROOT $ENV{PWD})

# This project uses vcpkg. We must then point to
# the corresponding toolchain file used so CMake
# can find dependencies.
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

# Setup initial project and project definitions.
project(${TUCKER_META_NAME} VERSION ${TUCKER_META_VERSION})

# Include these packages for build.
find_package(argparse CONFIG REQUIRED)
find_package(restclient-cpp CONFIG REQUIRED)

# Include this project application.
add_subdirectory(src)
