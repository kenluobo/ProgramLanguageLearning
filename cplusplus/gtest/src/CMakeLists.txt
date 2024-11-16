set(GOOGLETEST_DEMO_SRC_FILES testDynamicArray.cpp)

add_executable(googletestDemo ${GOOGLETEST_DEMO_SRC_FILES})

target_link_libraries(googletestDemo gtest)

target_include_directories(googletestDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_test(NAME testDemo COMMAND googletestDemo)
