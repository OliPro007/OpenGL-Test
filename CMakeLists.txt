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

#Install the executable and the resources 
file(GLOB RESOURCES RELATIVE "${CMAKE_SOURCE_DIR}" "OpenGL Test/*.vert" "OpenGL Test/*.frag" "OpenGL Test/*.obj" "OpenGL Test/*.mtl" "OpenGL Test/*.png" "OpenGL Test/*.bmp")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building for linux package...")
    add_definitions(-DLINUXRELEASE)
    install(TARGETS OpenGlTest DESTINATION /usr/bin)
    install(FILES ${RESOURCES} DESTINATION /usr/share/opengl-test)
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building locally...")
    install(TARGETS OpenGlTest DESTINATION /home/olivier/Documents/OpenGL-Test/bin)
    install(FILES ${RESOURCES} DESTINATION /home/olivier/Documents/OpenGL-Test/bin)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")
