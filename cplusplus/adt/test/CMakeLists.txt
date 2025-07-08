add_library(libTest
  STATIC
  TestSharedPtr.cpp
)

add_executable(mtest main.cpp)

target_link_libraries(mtest
  PRIVATE
  libTools
  gtest
)

target_include_directories(mtest
  PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)
