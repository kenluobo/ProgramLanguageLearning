set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(LIBS
    gtest
    gmock
    fmt::fmt
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CPP_SOURCE_FILES)

add_executable(cpp-exp ${CPP_SOURCE_FILES})

target_include_directories(cpp-exp PRIVATE ${INCLUDE_DIR})

target_link_libraries(cpp-exp PRIVATE ${LIBS})

add_test(NAME cpp-exp COMMAND cpp-exp)
