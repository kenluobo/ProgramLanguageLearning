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

# message(STATUS "Use customize libcxx:
# -- $ cmake -G Ninja -DCMAKE_CXX_FLAGS=\"-nostdinc++ -isystem /home/klb/Code/llvm-19.1.2/install-libcxx/include/c++/v1\" 
# --                  -DCMAKE_EXE_LINKER_FLAGS=\"-nostdlib++ -L/home/klb/Code/llvm-19.1.2/install-libcxx/lib -lc++ -lunwind -Wl,-rpath,/home/klb/Code/llvm-19.1.2/install-libcxx/lib\" 
# --                  ..")
if (DEFINED LLVM_LIBCXX_INSTALL_DIR)
    message(STATUS "Use LLVM_LIBCXX_INSTALL_DIR: ${LLVM_LIBCXX_INSTALL_DIR}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdinc++ -isystem ${LLVM_LIBCXX_INSTALL_DIR}/include/c++/v1")
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib++ -L${LLVM_LIBCXX_INSTALL_DIR}/lib -lc++ -lunwind -Wl,-rpath,${LLVM_LIBCXX_INSTALL_DIR}/lib")
    message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
endif()

# while use dynamic link way, fmt::fmt library required -fPIC option
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add result output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(LIBRARY_OUTPUT_DIR ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(INCLUDE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
    GIT_TAG 11.1.4
    VERSION 11.1.4
    OPTION
    "FMT_HEADER_ONLY=ON"
)

# add ctest
enable_testing()

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(tools)
