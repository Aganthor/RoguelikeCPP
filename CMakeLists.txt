cmake_minimum_required(VERSION 3.11)

project(Roguelike)

set(ROGUELIKE_VERSION_MAJOR 0)
set(ROGUELIKE_VERSION_MINOR 1)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(include/)
include_directories(Utility/)
include_directories(MapObjects/)

add_subdirectory(ecs)
add_subdirectory(MapObjects)
add_subdirectory(Utility)

add_executable(${PROJECT_NAME} main.cpp Engine.cpp Game.cpp Renderer.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libtcod.so ${CMAKE_SOURCE_DIR}/lib/libtcodgui.so ${SDL2_LIBRARIES} ecs map_objects utility)

set (source "${CMAKE_SOURCE_DIR}/res")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/res")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${destination} 
)

add_custom_command(
 TARGET ${PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
 COMMAND ${CMAKE_COMMAND} -E copy_directory ${source} ${destination} 
 DEPENDS ${destination}
 COMMENT "symbolic link resources folder from ${source} => ${destination}"
)
