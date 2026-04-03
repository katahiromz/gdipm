# CMakeLists.txt --- CMake project settings
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.10)

# project name and languages
project(gdipm C)

# Don't use DPI?
option(NO_DPI "Don't use DPI (dots per inch)" OFF)
if(NO_DPI)
    add_definitions(-DNO_DPI)
endif()

# gdipm.exe
add_executable(gdipm gdipm.c main.c)
target_link_libraries(gdipm gdi32 shlwapi uuid)
