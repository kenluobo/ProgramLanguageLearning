add_executable(do-testing testing.cpp)
target_include_directories(do-testing
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${robin-map_SOURCE_DIR}/include
)

target_link_libraries(do-testing
    PRIVATE
    pthread
)

#================================================================
add_executable(do-training training.cpp)

target_include_directories(do-training
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${robin-map_SOURCE_DIR}/include
)

target_link_libraries(do-training
    PRIVATE
    pthread
)
