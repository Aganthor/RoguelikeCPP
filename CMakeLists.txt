cmake_minimum_required(VERSION 3.11)

project(Roguelike)

set(ROGUELIKE_VERSION_MAJOR 0)
set(ROGUELIKE_VERSION_MINOR 1)

set(CMAKE_BUILD_TYPE "Debug")
if (CMAKE_BUILD_TYPE EQUAL "Debug")
	set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} -Wc++17-extensions -Wpragma-once-outside-header --debug")
else()
	set(CMAKE_CXX_COMPILE_FEATURES "${CMAKE_CXX_COMPILE_FEATURES} -Wc++17-extensions -Wpragma-once-outside-header")
endif()
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS)

if (APPLE)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
endif()
if (UNIX OR WIN32)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

include_directories(lib/libtcod/src/)
include_directories(lib/entt/src/)
include_directories(Utility/)
include_directories(MapObjects/)
include_directories(ecs/Components)
include_directories(ecs/systems)

add_subdirectory(MapObjects)
add_subdirectory(Utility)
add_subdirectory(ecs/systems)

add_executable(${PROJECT_NAME} main.cpp Engine.cpp Game.cpp Renderer.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/libtcod/libtcod.so ${SDL2_LIBRARIES} map_objects utility systems_objects)

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
