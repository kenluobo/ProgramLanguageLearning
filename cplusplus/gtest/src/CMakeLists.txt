#==============================================
set(TOOL_SRC_FILES
		Utils.cpp
)

set(TOOL_SRC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Tools ${LINK_TYPE} ${TOOL_SRC_FILES})

#==============================================
add_executable(app Main.cpp)

target_include_directories(app PRIVATE ${TOOLS_SRC_INCLUDE_DIR})

target_link_libraries(app PRIVATE Tools)
