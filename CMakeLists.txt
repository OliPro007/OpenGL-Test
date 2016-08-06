cmake_minimum_required(VERSION 2.8.9)

project(OpenGlTest)

include_directories("OpenGL Test")
include_directories("glm")

#Specify c++11 for g++ version before 6.1.0, as 6.1.0 defines c++14 as the default standard
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6.1.0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif()

#Set the compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    
mark_as_advanced(CMAKE_CXX_FLAGS_PACKAGE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
    "Choose the tye of build, options are: None Debug Release Package."
    FORCE)
else()
    set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the tye of build, options are: None Debug Release Package."
    FORCE)
endif()

#Define the sources and the executable
file(GLOB SOURCES "OpenGL Test/*.h" "OpenGL Test/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

#Include and link SDL and OpenGL
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

#Install the executable and the resources 
file(GLOB RESOURCES RELATIVE "${CMAKE_SOURCE_DIR}" "OpenGL Test/*.vert" "OpenGL Test/*.frag" "OpenGL Test/*.obj" "OpenGL Test/*.mtl" "OpenGL Test/*.png" "OpenGL Test/*.bmp")

if(CMAKE_BUILD_TYPE STREQUAL "Package")
    #message("*** ${CMAKE_BUILD_TYPE}: Building for linux package...")
    add_definitions(-DLINUXRELEASE)
    install(TARGETS OpenGlTest DESTINATION /usr/bin)
    install(FILES ${RESOURCES} DESTINATION /usr/share/opengl-test)
else()
    #message("*** ${CMAKE_BUILD_TYPE}: Building locally...")
    install(TARGETS OpenGlTest DESTINATION /home/olivier/Documents/OpenGL-Test/bin)
    install(FILES ${RESOURCES} DESTINATION /home/olivier/Documents/OpenGL-Test/bin)
endif()
