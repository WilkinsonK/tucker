# Wrapper script around cmake to make-ready this
# project as intended.

CMAKE_OPTIONS="\
-Bdist \
-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"

cmake ${CMAKE_OPTIONS} .
