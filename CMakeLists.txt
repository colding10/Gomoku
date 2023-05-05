cmake_minimum_required(VERSION 3.20)


# #
# Project settings
# #
project(gomoku)
set(CMAKE_CXX_STANDARD 17)

# #
# CMake Modules
# #
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


# #
# Source code
# #
add_library(gomolib STATIC
    src/gomolib/board.cpp
)

add_library(gomobot STATIC
    src/gomobot/searcher.cpp
)

add_executable(gomogui
    src/gomogui/main.cpp
    src/gomogui/eventhandler.cpp
)

# #
# Add external dependencies
# #
find_package(SDL2 REQUIRED)

target_link_libraries(gomobot PRIVATE gomolib)
target_link_libraries(gomogui PRIVATE gomolib)
target_link_libraries(gomogui PRIVATE gomobot)

target_link_libraries(gomogui PUBLIC ${SDL2_LIBRARIES})

target_include_directories(gomogui PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(gomogui PRIVATE src/gomolib)
target_include_directories(gomogui PRIVATE src/gomobot)
target_include_directories(gomobot PRIVATE src/gomolib)

# #
# Compilation settings
# #
set_target_properties(gomolib PROPERTIES OUTPUT_NAME "gomolib")
set_target_properties(gomobot PROPERTIES OUTPUT_NAME "gomobot")
set_target_properties(gomogui PROPERTIES OUTPUT_NAME "gomogui")
