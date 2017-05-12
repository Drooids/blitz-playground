cmake_minimum_required(VERSION 2.8)

project (blitz-playground)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

# I'm unsure what CP_CMAKE_DIR means
# googling gave only two results
set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)

# More on include:
# https://cmake.org/cmake/help/v3.5/command/include.html?highlight=include

include(cotire)
include(${CP_CMAKE_DIR}/macros.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_subdirectory(dependencies)

set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL/include )
set ( SDL2_LIBRARY SDL2 )

# set ( SDL2_IMAGE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL_image )
# set ( SDL2_IMAGE_LIBRARY SDL2_IMAGE )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++1y")

find_package(OpenGL REQUIRED)

set(BLITZ_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    # ${SDL2_IMAGE_LIBRARY}
)

set(BLITZ_INCLUDES
    ${SDL2_INCLUDE_DIR}
    # ${SDL2_IMAGE_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/
)

include_directories(${BLITZ_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/src )
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT game)
