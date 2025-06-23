add_library(libTest
  STATIC
  TestMSharedPtr.cpp
)

add_executable(mtest main.cpp)

target_link_libraries(mtest
  PRIVATE
  libTools
  gtest
)
