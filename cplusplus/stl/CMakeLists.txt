cmake_minimum_required(VERSION 3.24.2 FATAL_ERROR)

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

file(GLOB CPP_SOURCE_FILES "*.cpp")

foreach(CPP_FILE ${CPP_SOURCE_FILES})
	get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)
	add_executable(${FILE_NAME} ${CPP_FILE})
	target_include_directories(${FILE_NAME} PRIVATE utils)
endforeach ()
