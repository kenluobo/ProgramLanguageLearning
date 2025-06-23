add_library(libTools
  STATIC
  MSharedPtr.cpp
)

target_include_directories(libTools
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)
