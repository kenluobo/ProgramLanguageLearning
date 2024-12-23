set(TEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_LIBS
    Tools
    gtest
)

file(GLOB TEST_FILES "*.cpp")
add_executable(allTests ${TEST_FILES})
target_include_directories(allTests PRIVATE ${TEST_INCLUDE_DIR})
target_link_libraries(allTests PRIVATE ${TEST_LIBS})

enable_testing()
add_test(NAME allTests COMMAND allTests)
