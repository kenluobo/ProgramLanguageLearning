set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/old)

file(GLOB CPP_SOURCE_FILES "*.cpp")
foreach (CPP_FILE ${CPP_SOURCE_FILES})
  get_filename_component(TARGET ${CPP_FILE} NAME_WE)
  add_executable(${TARGET} ${CPP_FILE})
  target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/utils)
endforeach ()
