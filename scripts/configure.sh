# Wrapper script around cmake to make-ready this
# project as intended.

# -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
cmake -Bdist .
