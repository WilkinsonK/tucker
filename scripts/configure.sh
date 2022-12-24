# Wrapper script around cmake to make-ready this
# project as intended.

cmake -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake -Bdist .
