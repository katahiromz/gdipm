# CMakeLists.txt --- CMake project settings
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# project name and languages
project(gdipm C)

# Don't use DPI?
option(GDIPM_NO_DPI "Don't use DPI (dots per inch)" OFF)
if(GDIPM_NO_DPI)
    add_definitions(-DGDIPM_NO_DPI)
endif()

# libgdipm.a
add_library(libgdipm STATIC gdipm.c)
set_target_properties(libgdipm PROPERTIES PREFIX "")
target_link_libraries(libgdipm gdi32 shlwapi uuid libgdipm)

# gdipm.exe
add_executable(gdipm main.c)
target_link_libraries(gdipm libgdipm)
