file(GLOB CPP_SOURCE_FILES "*.cpp")
foreach (CPP_FILE ${CPP_SOURCE_FILES})
  get_filename_component(TARGET ${CPP_FILE} NAME_WE)
  add_executable(${TARGET} ${CPP_FILE})
  target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(${TARGET} PRIVATE fmt::fmt)
  target_link_options(${TARGET} PRIVATE "-static")
endforeach ()

