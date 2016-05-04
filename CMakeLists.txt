cmake_minimum_required(VERSION 2.8.9)

project(OpenGlTest)

include_directories("OpenGL Test")
include_directories("glm")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

file(GLOB SOURCES "OpenGL Test/*.h" "OpenGL Test/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

#Include and link SDL and OpenGL
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
find_package(OpenGL REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${OPENGL_LIBRARIES})

#Copy the resources to the build directory and delete them on make clean
file(GLOB RESOURCES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL Test/" "OpenGL Test/*.vert" "OpenGL Test/*.frag" "OpenGL Test/*.obj" "OpenGL Test/*.mtl" "OpenGL Test/*.png" "OpenGL Test/*.bmp")

foreach(item IN LISTS RESOURCES)
    message(STATUS ${item})
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}" 
                        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL Test/${item}" ${CMAKE_CURRENT_BINARY_DIR}
                        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/OpenGL Test/${item}")
endforeach()

add_custom_target(resource-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES}")