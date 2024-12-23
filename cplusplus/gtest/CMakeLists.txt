cmake_minimum_required(VERSION 3.24.2 FATAL_ERROR)

# set compiler
find_program(CLANG "clang")
if (CLANG)
  set(CMAKE_C_COMPILER ${CLANG})
  message(STATUS "C compiler: ${CLANG}")
endif ()

find_program(CLANG_PLUS_PLUS "clang++")
if (CLANG_PLUS_PLUS)
  set(CMAKE_CXX_COMPILER ${CLANG_PLUS_PLUS})
  message(STATUS "CXX compiler: ${CLANG_PLUS_PLUS}")
endif ()

project(
    "googleTestDemo"
    VERSION "0.0.1"
    DESCRIPTION "Learn google test framework")

# set language standard
set(CMAKE_C_STANDARD 17)
message(STATUS "C language standard: ${CMAKE_C_STANDARD}")

set(CMAKE_CXX_STANDARD 20)
message(STATUS "CXX language standard: ${CMAKE_CXX_STANDARD}")

# generate compile database
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
message(STATUS "Generate compile database file compile_commands.json")

# config build type
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif ()

# set link type
option(ENABLE_BUILD_SHARED "Use shared link" ON)
if (${ENABLE_BUILD_SHARED})
  set(LINK_TYPE SHARED)
  message(STATUS "Use dynamic link way")
elseif ()
  set(LINK_TYPE STATIC)
  message(STATUS "Use static link way")
endif ()

# set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(LIBRARY_OUTPUT_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(INCLUDE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/include")

# add third party library from github, manage by cpm download third party source
# file and store ${CMAKE_SOURCE_DIR}/third-party
set(CPM_SOURCE_CACHE "${CMAKE_BINARY_DIR}/third-party")

include(cmake/CPM.cmake)
cpmaddpackage(
    NAME googletest
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.15.2
    VERSION 1.15.2
    OPTIONS
    "INSTALL_GTEST OFF"
    "gtest_force_shared_crt"
)

option(ENABLE_TESTS "Run test cases" ON)
if (${ENABLE_TESTS})
  enable_testing()
  message(STATUS "Enable all tests")
endif ()

# source files
add_subdirectory(src)
add_subdirectory(test)
