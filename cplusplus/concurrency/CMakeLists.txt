cmake_minimum_required(VERSION 3.24.2 FATAL_ERROR)

find_program(CLANG_C_COMPILER "clang")
if (CLANG_C_COMPILER)
  set(CMAKE_C_COMPILER ${CLANG_C_COMPILER} CACHE STRING "C Compiler" FORCE)
  message(STATUS "Find and use ${CMAKE_C_COMPILER}")
else ()
  message(STATUS "Can't find clang, use default c compiler: ${CMAKE_C_COMPILER}")
endif ()

find_program(CLANG_CXX_COMPILER "clang++")
if (CLANG_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER ${CLANG_CXX_COMPILER} CACHE STRING "CXX Compiler" FORCE)
  message(STATUS "Find and use ${CMAKE_CXX_COMPILER}")
else ()
  message(STATUS "Can't find clang++, use default c++ compiler: ${CMAKE_CXX_COMPILER}")
endif ()

project(
    "learn-standard-library"
    VERSION 0.1
    DESCRIPTION "learn cplusplus standard library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED NO)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

# Include CPM for package management
set(CPM_DOWNLOAD_VERSION 0.36.0)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
  file(DOWNLOAD
       https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
       ${CPM_DOWNLOAD_LOCATION}
  )
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Add fmt library
CPMAddPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 9.1.0
  OPTIONS
    "FMT_INSTALL OFF"
)

file(GLOB CPP_SOURCE_FILES "*.cpp")

foreach (CPP_FILE ${CPP_SOURCE_FILES})
  get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
  add_executable(${FILE_NAME} ${CPP_FILE})
  target_include_directories(${FILE_NAME} PRIVATE utils)
  target_link_libraries(${FILE_NAME} PRIVATE Threads::Threads fmt::fmt)
endforeach ()

