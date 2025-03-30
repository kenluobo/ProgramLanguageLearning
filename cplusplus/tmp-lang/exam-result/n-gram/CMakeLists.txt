add_executable(do-testing testing.cpp)
target_include_directories(do-testing
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(do-training training.cpp)
target_include_directories(do-training
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
