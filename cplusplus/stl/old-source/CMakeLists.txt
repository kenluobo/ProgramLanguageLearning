set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/old)

file(GLOB CPP_SOURCE_FILES "*.cpp")
foreach (CPP_FILE ${CPP_SOURCE_FILES})
  get_filename_component(TARGET ${CPP_FILE} NAME_WE)
  add_executable(${TARGET} ${CPP_FILE})
  target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/utils)
  # fixme: define llvm libcxx link option
  #  target_link_options(${TARGET}
  #      PRIVATE
  #      -nostdinc++ -isystem ${DEFAULT_CXX_INCLUDE_DIR}
  #      -nostdlib++
  #      -Wl,-rpath,${DEFAULT_CXX_LIB_DIR}
  #      -L ${DEFAULT_CXX_LIB_DIR}
  #      -lc++
  #      -lc++abi
  #      -lc++experimental
  #      -lunwind
  #      -Wl,-rpath,/lib/x86_64-linux-gnu/
  #      -L/lib/x86_64-linux-gnu/
  #      -lc
  #      -lm
  #      -lrt
  #      -ldl
  #      -lgcc_s
  #      -lpthread
  #  )

endforeach ()
