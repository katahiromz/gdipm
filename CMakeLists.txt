# CMakeLists.txt --- CMake project settings
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# project name, version, and languages
project(gdipm VERSION 1.8 LANGUAGES C)

# project version macro
add_definitions(-DGDIPM_VERSION="${gdipm_VERSION}")

# "Don't use DPI?" Option
option(GDIPM_NO_DPI "Don't use DPI (dots per inch)" OFF)
if(GDIPM_NO_DPI)
    add_definitions(-DGDIPM_NO_DPI)
endif()

# "Don't make test program?" Option
option(GDIPM_NO_TESTS "Don't create test programs" ON)
if(GDIPM_NO_TESTS)
    add_definitions(-DGDIPM_NO_TESTS)
endif()

# libgdipm.a
add_library(libgdipm STATIC gdipm.c)
set_target_properties(libgdipm PROPERTIES PREFIX "")
target_include_directories(libgdipm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(libgdipm gdi32 shlwapi uuid)

if(NOT GDIPM_NO_TESTS)
    # gdipm.exe
    add_executable(gdipm main.c)
    target_link_libraries(gdipm libgdipm)
endif()

# display status
message(STATUS "GDIPM_NO_DPI = ${GDIPM_NO_DPI}")
message(STATUS "GDIPM_NO_TESTS = ${GDIPM_NO_TESTS}")
