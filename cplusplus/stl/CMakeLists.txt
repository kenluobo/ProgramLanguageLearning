cmake_minimum_required(VERSION 3.24.2 FATAL_ERROR)

include(cmake/find_clang.cmake)
set_clang_as_c_compiler()
set_clang_plusplus_as_cxx_compiler()

project(
    "learn-standard-library"
    VERSION 0.1
    DESCRIPTION "learn cplusplus standard library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED NO)

# while use dynamic link way, fmt::fmt library required -fPIC option
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add result output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(INCLUDE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/include)

# add cpm download directory
set(CPM_SOURCE_CACHE ${CMAKE_BINARY_DIR}/third-party)

# add gtest and gmock library
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

# add format library
cpmaddpackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt
    GIT_TAG 11.0.2
    VERSION 11.0.2
    OPTION
    "FMT_HEADER_ONLY=ON"
)

# use llvm libcxx
if (DEFINED LLVM_LIB_CXX_DIR)
  message(STATUS "Use llvm libcxx and specify ${LLVM_LIB_CXX_DIR}")

  set(DEFAULT_CXX_INCLUDE_DIR "${LLVM_LIB_CXX_DIR}/include/c++/v1")
  message(STATUS "Default include search directory: ${DEFAULT_CXX_INCLUDE_DIR}")

  set(DEFAULT_CXX_LIB_DIR "${LLVM_LIB_CXX_DIR}/lib")
  message(STATUS "Default library search directory: ${DEFAULT_CXX_LIB_DIR}")
endif ()

# add ctest
enable_testing()

add_subdirectory(old-source)
add_subdirectory(source)
